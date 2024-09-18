/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** Core
*/

#include <iostream>
#include "Core.hpp"
#include "AEvent.hpp"
#include "AObject.hpp"
#include "CoreMenu.hpp"

arcade::Core::Core(std::string const &lib) :
m_run(true), m_isPaused(true), m_exitValue(0)
{
    try {
        m_graphicsLoader.open(lib);
        m_graphicsModule = m_graphicsLoader.getSym("entryPoint");

        m_coreMenuLoader.open("./arcade_menu.so");
        m_gameModule = m_coreMenuLoader.getSym("entryPoint");

    } catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
        m_run = false;
        m_exitValue = 84;
        return;
    }
    m_mapOfEventPause = {
        {"Enter", &Core::enterEvent},
        {"Escape", &Core::play},
        {"Switch", &Core::switchGraphicRunTime},
    };
    m_mapOfEventPlay = {
        {"Escape", &Core::pause},
        {"Switch", &Core::switchGraphicRunTime},
    };
    loop();
}

arcade::Core::~Core()
{
    m_gameModule.reset();
    m_gamePaused.reset();
    m_graphicsModule.reset();
    m_gameLoader.close();
    m_graphicsLoader.close();
}

int arcade::Core::getExitValue(void) const
{
    return m_exitValue;
}

bool arcade::Core::pause(void)
{
    if (m_isPaused) {
        return false;
    }
    m_gamePaused.swap(m_gameModule);
    m_isPaused = true;
    return false;
}

bool arcade::Core::play(void)
{
    if (!m_isPaused || !m_gamePaused) {
        return false;
    }
    m_gamePaused.swap(m_gameModule);
    m_isPaused = false;
    return false;
}

void arcade::Core::openGameInPause(std::string const &libName)
{

    try {
        m_gamePaused.reset();
        m_gameLoader.open(libName);
        m_gamePaused = m_gameLoader.getSym("entryPoint");
    }
    catch(DLLdr::DLLoaderException const &e) {
        std::cerr << e.what() << '\n';
        m_run = false;
        m_exitValue = 84;
        return;
    }
    catch (std::bad_alloc const &e) {
        std::cerr << e.what() << '\n';
        m_run = false;
        m_exitValue = 84;
        return;
    }
    
}

void arcade::Core::openNewGraphics(std::string const &libName)
{
    try {
        m_graphicsModule.reset();
        m_graphicsLoader.open(libName);
        m_graphicsModule = m_graphicsLoader.getSym("entryPoint");
    }
    catch(DLLdr::DLLoaderException const &e) {
        std::cerr << e.what() << '\n';
        m_run = false;
        m_exitValue = 84;
        return;
    }
    catch (std::bad_alloc const &e) {
        std::cerr << e.what() << '\n';
        m_run = false;
        m_exitValue = 84;
        return;
    }
}

bool arcade::Core::switchGraphicRunTime(void)
{
    std::vector<std::unique_ptr<IEvent>> events;
    events.push_back(std::make_unique<arcade::AEvent>("Switch"));
    (!m_isPaused ? m_gamePaused : m_gameModule)->manageEvent(events);
    data_t const &data = (!m_isPaused ? m_gamePaused : m_gameModule)->getMap();
    if (data.objects.size() == 0 || data.objects[0]->getAscii() != Focus::Graphics) {
        return false;
    }
    std::string libName = data.objects[0]->getAsset();
    openNewGraphics(libName);
    (!m_isPaused ? m_gamePaused : m_gameModule)->iterate();
    return false;
}

bool arcade::Core::enterEvent(void)
{
    std::vector<std::unique_ptr<IEvent>> events;
    events.push_back(std::make_unique<arcade::AEvent>("Enter"));

    m_gameModule->manageEvent(events);
    data_t const &data = m_gameModule->getMap();
    std::string libName = data.objects[0]->getAsset();
    arcade::Focus type = (arcade::Focus)data.objects[0]->getAscii();
    m_gameModule->iterate();
    if (type == Focus::Graphics) {
        openNewGraphics(libName);
        return false;
    }
    if (type == Focus::Games) {
        openGameInPause(libName);
        play();
        return false;
    }
    if (type == Focus::Name) {
        m_userName = data.objects[0]->getAsset();
        return false;
    }
    return false;
}

void arcade::Core::checkQuit(std::vector<std::unique_ptr<IEvent>> const &events)
{
    for (auto it = events.begin(); it != events.end(); ++it) {
        if ((*it)->type() == "Quit") {
            m_run = false;
            return;
        }
    }
}

void arcade::Core::manageEvent(std::vector<std::unique_ptr<IEvent>> const &events)
{
    if (events.size() == 0) {
        m_gameModule->iterate();
        return;
    }
    std::string event = events[0]->type();

    auto finder = ((m_isPaused == true) ? m_mapOfEventPause : m_mapOfEventPlay).find(event);
    if (finder != ((m_isPaused == true) ? m_mapOfEventPause : m_mapOfEventPlay).end()) {
        if (((finder->second))(*this) == false) {
            return;
        }
    }
    m_gameModule->manageEvent(events);
    m_gameModule->iterate();
    checkQuit(events);
}

void arcade::Core::loop(void)
{

    while (m_run) {
        manageEvent(m_graphicsModule->getEvent());
        if (m_exitValue != 0) {
            return;
        }
        m_graphicsModule->clear();
        m_graphicsModule->display(m_gameModule->getMap());
    }
}
