/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** SnakeMenu
*/

#include "SnakeMenu.hpp"
#include "AObject.hpp"
#include "Arcade.hpp"

SnakeMenu::SnakeMenu()
{
    m_menuRunning = true;
    m_data.objects.clear();
    std::string txt = "Press any arrow-key to start";
    m_data.size = {50 , 25};
    int x = m_data.size.first / 2 - txt.length() / 2;
    m_data.objects.push_back(std::make_unique<arcade::AObject>(255, 255, 255, x, m_data.size.second / 2, txt.length(), 2, txt, 0, arcade::Text));
}

void SnakeMenu::manageEvent(std::vector<std::unique_ptr<arcade::IEvent>> const &events)
{
    if (events.size() == 0) {
        return;
    } else {
        if (events[0]->type() == "Down" || events[0]->type() == "Up" || events[0]->type() == "Left" || events[0]->type() == "Right")
            m_menuRunning = false;
    }
}

void SnakeMenu::iterate(void)
{
    return;
}

arcade::data_t const &SnakeMenu::getMap(void) const
{
    return m_data;
}

bool SnakeMenu::isRunning() const
{
    return m_menuRunning;
}

void SnakeMenu::setMenuRunning(bool running)
{
    m_menuRunning = running;
}
