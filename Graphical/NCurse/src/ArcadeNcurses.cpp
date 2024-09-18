/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** ArcadeNcurses
*/

#include <ncurses.h>
#include <exception>
#include <memory>
#include <vector>

#include "ArcadeNcurses.hpp"
#include "AEvent.hpp"

arcade::ArcadeNcurses::ArcadeNcurses() :
m_nb_colors(8), m_nb_pairs(0)
{
    initscr();
    raw();
    cbreak();
    keypad(stdscr, true);
    noecho();
    curs_set(0);
    start_color();
    timeout(0);
    m_colors = {
        {{0, 0, 0}, COLOR_BLACK},
        {{1000, 0, 0}, COLOR_RED},
        {{0, 1000, 0}, COLOR_GREEN},
        {{0, 0, 1000}, COLOR_BLUE},
        {{1000, 1000, 0}, COLOR_YELLOW},
        {{1000, 0, 1000}, COLOR_MAGENTA},
        {{0, 1000, 1000}, COLOR_CYAN},
        {{1000, 1000, 1000}, COLOR_WHITE},
    };

    m_mapOfEvents = {
        {'\t', "Switch"},
        {KEY_BACKSPACE, "Back Space"},
        {KEY_UP, "Up"},
        {KEY_DOWN, "Down"},
        {KEY_LEFT, "Left"},
        {KEY_RIGHT, "Right"},
        {27, "Escape"}, // KEY_ESC
        {'\n', "Enter"} // You may need to define KEY_ENTER if not available
    };
}

arcade::ArcadeNcurses::~ArcadeNcurses()
{
    endwin();
}

void arcade::ArcadeNcurses::clear()
{
    ::werase(stdscr);
}

unsigned short arcade::ArcadeNcurses::getColor(int r, int g, int b)
{
    std::array<unsigned short, 3> color = {
        static_cast<unsigned short>(r * 1000 / 255),
        static_cast<unsigned short>(g * 1000 / 255),
        static_cast<unsigned short>(b * 1000 / 255)
    };

    auto finder = m_colors.find(color);
    if (finder == m_colors.end()) {
        m_colors.insert({color, m_nb_colors});
        init_color(m_nb_colors, color[0], color[1], color[2]);
        m_nb_colors++;
        return m_nb_colors - 1;
    }
    return finder->second;
}

unsigned short arcade::ArcadeNcurses::getPair(unsigned short foreground, unsigned short background)
{
    std::array<unsigned short, 2> pair = {
        foreground,
        background
    };

    auto finder = m_pairs.find(pair);
    if (finder == m_pairs.end()) {
        m_pairs.insert({pair, m_nb_pairs});
        init_pair(m_nb_pairs, pair[0], pair[1]);
        m_nb_pairs++;
        return m_nb_pairs - 1;
    }
    return finder->second;
    return 0;
}

void arcade::ArcadeNcurses::manageSingelObject(std::unique_ptr<IObject> const &object)
{
    int x = object->getPos()[0];
    int y = object->getPos()[1];

    if (object->getType() == arcade::Type::Graphic) {
        short color = getColor(object->getRGB()[0], object->getRGB()[1], object->getRGB()[2]);
        attron(COLOR_PAIR(getPair(color, color)));
        size_t width = object->getSize()[0];
        size_t height = object->getSize()[1];
        for (size_t i = 0; i < height; ++i) {
            for (size_t j = 0; j < width; ++j) {
                mvaddch(i + y, j + x, object->getAscii());
            }
        }
        attroff(COLOR_PAIR(getPair(color, color)));
    } else {
        short foreground = getColor(object->getRGB()[0], object->getRGB()[1], object->getRGB()[2]);
        short background = getColor(255 - object->getRGB()[0], 255 - object->getRGB()[1], 255 - object->getRGB()[2]);
        attron(COLOR_PAIR(getPair(foreground, background)));
        mvaddstr(y, x, object->getAsset().c_str());
        attroff(COLOR_PAIR(getPair(foreground, background)));
    }
}

void arcade::ArcadeNcurses::display(data_t const &objects)
{
    for (auto &object : objects.objects) {
        manageSingelObject(object);
    }
    wrefresh(stdscr);
}

std::vector<std::unique_ptr<arcade::IEvent>> const &arcade::ArcadeNcurses::getEvent(void)
{
    m_eventGlobal.clear();
    int ch = getch();

    if (ch != ERR) {
        if (ch == KEY_DC || ch == 127) {
            m_eventGlobal.push_back(std::make_unique<arcade::AEvent>("Quit"));
            return m_eventGlobal;
        }
        auto finder = m_mapOfEvents.find(ch);
        if (finder != m_mapOfEvents.end()) {
            m_eventGlobal.push_back(std::make_unique<arcade::AEvent>(finder->second));
            return m_eventGlobal;
        }
        std::string key = std::string(1, std::toupper(ch));
        m_eventGlobal.push_back(std::make_unique<arcade::AEvent>(key));
    }
    return m_eventGlobal;
}
