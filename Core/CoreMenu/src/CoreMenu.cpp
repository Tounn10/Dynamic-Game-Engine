/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** CoreMenu
*/

#include "AObject.hpp"
#include "CoreMenu.hpp"
#include <regex>
#include <algorithm>
#include <memory>

extern "C" std::unique_ptr<arcade::IGameModule> entryPoint()
{
    return std::make_unique<arcade::CoreMenu>();
}

arcade::CoreMenu::CoreMenu() :
m_folder("./lib"), m_focus(Focus::Games),
m_gamesManager("./lib", "games", "", m_gamesPossible),
m_graphicsManager("./lib", "graphics", "", m_graphicsPossible)
{
    m_graphicsPossible = {
        "arcade_sdl2.so",
        "arcade_ncurses.so",
        "arcade_ndk++.so",
        "arcade_aalib.so",
        "arcade_libcaca.so",
        "arcade_allegro5.so",
        "arcade_xlib.so",
        "arcade_gtk+.so",
        "arcade_sfml.so",
        "arcade_irrlicht.so",
        "arcade_opengl.so",
        "arcade_vulkan.so",
        "arcade_qt5.so"
    };
    m_gamesPossible = {
        "arcade_snake.so",
        "arcade_nibbler.so",
        "arcade_pacman.so",
        "arcade_qix.so",
        "arcade_centipede.so",
        "arcade_solarfox.so"
    };
    updateLibsAvailable();
    m_mapOfEvent = {
        {"Switch", &CoreMenu::switchRunTime},
        {"R", &CoreMenu::updateLibsAvailable},
        {"Enter", &CoreMenu::select},
        {"Down", &CoreMenu::moveFocusDown},
        {"Up", &CoreMenu::moveFocusUp},
        {"Left", &CoreMenu::moveFocusLeft},
        {"Right", &CoreMenu::moveFocusRight}
    };
    m_data.size = {60, 25};
}

arcade::CoreMenu::~CoreMenu()
{
    m_data.objects.clear();
}

arcade::data_t const &arcade::CoreMenu::getMap() const
{
    return m_data;
}

void arcade::CoreMenu::addToDisplayName(std::string const &name, int x, int y)
{
    char color = 150;
    if (m_focus == Focus::Name) {
        color = 255;
    }
    m_data.objects.push_back(std::make_unique<AObject>(color, color, color, x, y, 1, 1, name, ' ', Text));
}

void arcade::CoreMenu::iterate(void)
{
    m_data.objects.clear();
    m_gamesManager.addData(m_data.objects, 1, 8, 20, (m_focus == Focus::Games));
    m_graphicsManager.addData(m_data.objects, 30, 8, 20, (m_focus == Focus::Graphics));
    addToDisplayName("Name: " + m_userName, 1, 5);

    m_data.objects.push_back(std::make_unique<AObject>(255, 255, 255, 1, 2, 1, 1, "Quit: Suppr", ' ', Text));
    m_data.objects.push_back(std::make_unique<AObject>(255, 255, 255, 1, 3, 1, 1, "Play/Pause: Esc", ' ', Text));
    m_data.objects.push_back(std::make_unique<AObject>(255, 255, 255, 1, 4, 1, 1, "Refresh: R", ' ', Text));
    m_data.objects.push_back(std::make_unique<AObject>(255, 255, 255, 1, 7, 1, 1, "Games", ' ', Text));
    m_data.objects.push_back(std::make_unique<AObject>(255, 255, 255, 30, 7, 1, 1, "Menu", ' ', Text));
}

void arcade::CoreMenu::moveFocusDown(void)
{
    if (m_focus == Focus::Games) {
        m_gamesManager.moveFocus("Down");
    }
    if (m_focus == Focus::Graphics) {
        m_graphicsManager.moveFocus("Down");
    }
}

void arcade::CoreMenu::moveFocusUp(void)
{
    if (m_focus == Focus::Games) {
        m_gamesManager.moveFocus("Up");
    }
    if (m_focus == Focus::Graphics) {
        m_graphicsManager.moveFocus("Up");
    }
}

void arcade::CoreMenu::moveFocusLeft(void)
{
    m_focus = (Focus)(((int)m_focus - 1 + (int)NB_Focus) % (int)NB_Focus);
}

void arcade::CoreMenu::moveFocusRight(void)
{
    m_focus = (Focus)(((int)m_focus + 1) % (int)NB_Focus);
}

void arcade::CoreMenu::select(void)
{
    m_data.objects.clear();
    std::string data;
    if (m_focus == Focus::Graphics) {
        data = m_graphicsManager.select();
    }
    if (m_focus == Focus::Games) {
        data = m_gamesManager.select();
    }
    if (m_focus == Focus::Name) {
        data = m_userName;
    }
    m_data.objects.push_back(std::make_unique<AObject>(0, 0, 0, 0, 0, 0, 0, data, m_focus, Graphic));
}

void arcade::CoreMenu::switchRunTime(void)
{
    m_graphicsManager.update();
    m_data.objects.clear();
    m_graphicsManager.moveFocus("Down");
    std::string nameLib = m_graphicsManager.select();
    m_data.objects.push_back(std::make_unique<AObject>(0, 0, 0, 0, 0, 0, 0, nameLib, Focus::Graphics, Graphic));
}

void arcade::CoreMenu::manageEvent(std::vector<std::unique_ptr<IEvent>> const &events)
{
    if (events.size() == 0) {
        return;
    }
    std::string event = events[0]->type();

    if (m_focus == Focus::Name) {
        if (event == "Back Space" && m_userName.size() > 0) {
            m_userName.pop_back();
        }
        if (event.size() == 1) {
            m_userName += event;
            return;
        }
    }

    auto finder = m_mapOfEvent.find(event);
    if (finder != m_mapOfEvent.end()) {
        finder->second(*this);
    }
}

void arcade::CoreMenu::updateLibsAvailable(void)
{
    if (m_focus == Focus::Graphics || m_focus == Focus::Games) {
        m_gamesManager.update();
        m_graphicsManager.update();
    }
}
