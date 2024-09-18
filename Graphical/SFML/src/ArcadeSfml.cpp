/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** ArcadeSfml
*/

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <exception>
#include <memory>
#include <vector>
#include <algorithm>

#include "ArcadeSfml.hpp"
#include "AEvent.hpp"

arcade::ArcadeSfml::ArcadeSfml() :
m_window(sf::VideoMode(1920, 1080), "SFML Arcade", sf::Style::Close)
{
    m_window.setSize(sf::Vector2u(1920, 1080));
    if (m_backgroundTexture.loadFromFile("assets/background.png")) {
        m_backgroundSprite.setTexture(m_backgroundTexture);
        m_backgroundSprite.setScale(static_cast<float>(m_window.getSize().x) / m_backgroundTexture.getSize().x, 
                                    static_cast<float>(m_window.getSize().y) / m_backgroundTexture.getSize().y);
    }

    m_mapOfEvents = {
        {sf::Keyboard::Key::A, "A"},
        {sf::Keyboard::Key::B, "B"},
        {sf::Keyboard::Key::C, "C"},
        {sf::Keyboard::Key::D, "D"},
        {sf::Keyboard::Key::E, "E"},
        {sf::Keyboard::Key::F, "F"},
        {sf::Keyboard::Key::G, "G"},
        {sf::Keyboard::Key::H, "H"},
        {sf::Keyboard::Key::I, "I"},
        {sf::Keyboard::Key::J, "J"},
        {sf::Keyboard::Key::K, "K"},
        {sf::Keyboard::Key::L, "L"},
        {sf::Keyboard::Key::M, "M"},
        {sf::Keyboard::Key::N, "N"},
        {sf::Keyboard::Key::O, "O"},
        {sf::Keyboard::Key::P, "P"},
        {sf::Keyboard::Key::Q, "Q"},
        {sf::Keyboard::Key::R, "R"},
        {sf::Keyboard::Key::S, "S"},
        {sf::Keyboard::Key::T, "T"},
        {sf::Keyboard::Key::U, "U"},
        {sf::Keyboard::Key::V, "V"},
        {sf::Keyboard::Key::W, "W"},
        {sf::Keyboard::Key::X, "X"},
        {sf::Keyboard::Key::Y, "Y"},
        {sf::Keyboard::Key::Z, "Z"},
        {sf::Keyboard::Key::Tab, "Switch"},
        {sf::Keyboard::Key::Up, "Up"},
        {sf::Keyboard::Key::Down, "Down"},
        {sf::Keyboard::Key::Left, "Left"},
        {sf::Keyboard::Key::Right, "Right"},
        {sf::Keyboard::Key::Escape, "Escape"},
        {sf::Keyboard::Key::Enter, "Enter"},
        {sf::Keyboard::Delete, "Quit"},
        {sf::Keyboard::BackSpace, "Back Space"}
    };

    m_manageFunc = {
        {arcade::Type::Text, &ArcadeSfml::manageText},
        {arcade::Type::Graphic, &ArcadeSfml::manageGraphical},
        {arcade::Type::Font, &ArcadeSfml::manageFont}
    };

    m_window.setFramerateLimit(60);
    if (!m_window.isOpen())
        throw std::exception();
    this->setFont("assets/pok.ttf");
    m_text.setFillColor(sf::Color(0, 0, 0));
}

arcade::ArcadeSfml::~ArcadeSfml()
{
    m_window.close();
}

void arcade::ArcadeSfml::clear()
{
    m_window.clear(sf::Color(0, 0, 0, 255));
}

void arcade::ArcadeSfml::setTexture(std::string const &asset, sf::Color const &color)
{
    if (asset == "") {
        m_rect.setTexture(nullptr);
        m_rect.setFillColor(color);
        return;
    }
    auto finder1 = m_files.find(asset);
    if (finder1 != m_files.end()) {
        if (finder1->second == false) {
            m_rect.setTexture(nullptr);
            m_rect.setFillColor(color);
            return;
        }
    }
    auto finder = m_textureMap.find(asset);
    if (finder == m_textureMap.end()) {
        sf::Texture new_texture;
        if (new_texture.loadFromFile(asset)) {
            m_textureMap.insert({asset, new_texture});
            m_rect.setFillColor(sf::Color(255, 255, 255, 255));
            m_rect.setTexture(&new_texture);
            m_files.insert({asset, true});
        } else {
            m_rect.setTexture(nullptr);
            m_files.insert({asset, false});
            return;
        }
    } else {
        m_rect.setFillColor(sf::Color(255, 255, 255, 255));
        m_rect.setTexture(&(*finder).second);
    }
    return ;
}

void arcade::ArcadeSfml::setFont(std::string const &path)
{
    if (path == "")
        return;
    
    auto finder = m_fontMap.find(path);
    if (finder != m_fontMap.end()) {
        m_text.setFont(m_fontMap.at(path));
    } else {
        sf::Font new_font;
        if (new_font.loadFromFile(path)) {
            m_fontMap.insert({path, new_font});
            m_text.setFont(m_fontMap.at(path));
            m_files.insert({path, true});
        } else {
            m_files.insert({path, false});
        }
    }
}

void arcade::ArcadeSfml::manageFont(std::unique_ptr<IObject> const &object,
    __attribute__((unused)) int min,
    __attribute__((unused)) int windowCenterX,
    __attribute__((unused)) int windowCenterY)
{
    setFont(object->getAsset());
}

void arcade::ArcadeSfml::manageGraphical(std::unique_ptr<IObject> const &object, int min, int windowCenterX, int windowCenterY)
{
    setTexture(object->getAsset(), sf::Color(object->getRGB()[0], object->getRGB()[1], object->getRGB()[2]));
    m_rect.setSize(sf::Vector2f(object->getSize()[0] * min, object->getSize()[1] * min));
    m_rect.setPosition(sf::Vector2f(windowCenterX, windowCenterY) + sf::Vector2f(object->getPos()[0] * min, object->getPos()[1] * min));
    m_window.draw(m_rect);
}

void arcade::ArcadeSfml::manageText(std::unique_ptr<IObject> const &object, int min, int windowCenterX, int windowCenterY)
{
    m_text.setFillColor(sf::Color(object->getRGB()[0], object->getRGB()[1], object->getRGB()[2]));
    m_text.setString(object->getAsset());
    m_text.setCharacterSize(static_cast<unsigned int>(min) * object->getSize()[1]);
    m_text.setPosition(sf::Vector2f(windowCenterX, windowCenterY) + sf::Vector2f(object->getPos()[0] * min, object->getPos()[1] * min));
    m_window.draw(m_text);
}

void arcade::ArcadeSfml::display(data_t const &objects)
{

    sf::IntRect textureRect(0, 0, m_window.getSize().x, m_window.getSize().y);
    sf::Sprite backgroundSprite(m_backgroundTexture, textureRect);
    m_window.draw(m_backgroundSprite);

    sf::RectangleShape blackSquare(sf::Vector2f(objects.size.first * 25, objects.size.second * 25));
    blackSquare.setFillColor(sf::Color::Black);
    blackSquare.setPosition((m_window.getSize().x - blackSquare.getSize().x) / 2, (m_window.getSize().y - blackSquare.getSize().y) / 2);
    m_window.draw(blackSquare);

    int scaleX = (objects.size.first == 0) ? 25 : static_cast<int>(m_window.getSize().x) / objects.size.first;
    int scaleY = (objects.size.second == 0) ? 25 : static_cast<int>(m_window.getSize().y) / objects.size.second;

    size_t min = std::min(scaleX, scaleY);
    if (min > 25)
        min = 25;
    int windowCenterX = m_window.getSize().x / 2;
    int windowCenterY = m_window.getSize().y / 2;
    windowCenterX -= (objects.size.first * min) / 2;
    windowCenterY -= (objects.size.second * min) / 2;

    if (!m_window.isOpen())
        throw std::exception();
    for (auto it = objects.objects.begin(); it != objects.objects.end(); ++it) {
        auto fct = m_manageFunc.find((*it)->getType());
        if (fct != m_manageFunc.end()) {
            fct->second(*this, *it, min, windowCenterX, windowCenterY);
        }
    }
    m_window.display();
}

std::vector<std::unique_ptr<arcade::IEvent>> const &arcade::ArcadeSfml::getEvent(void)
{
    m_eventGlobal.clear();

    while (m_window.pollEvent(m_event)) {
        if (m_event.type == sf::Event::KeyPressed) {
            auto it = m_mapOfEvents.find(m_event.key.code);
            if (it != m_mapOfEvents.end()) {
                m_eventGlobal.push_back(std::make_unique<AEvent>((*it).second));
            }
        } else if (m_event.type == sf::Event::Resized) {
            if (m_event.size.width > 1920 || m_event.size.height > 1080) {
                m_window.setSize(sf::Vector2u(1920, 1080));
            }
        } if (m_event.type == sf::Event::Closed) {
            m_eventGlobal.push_back(std::make_unique<AEvent>("Quit"));
        }
    }
    return m_eventGlobal;
}
