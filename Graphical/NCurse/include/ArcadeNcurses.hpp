/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** ArcadeNcurses
*/

#include <vector>
#include <map>

#include "Arcade.hpp"
#include "Pixel.hpp"

#ifndef ARCADESFML_HPP_
    #define ARCADESFML_HPP_

namespace arcade {
    class ArcadeNcurses : public arcade::IDisplayModule {
        public:
            ArcadeNcurses();
            ~ArcadeNcurses();
            void display(data_t const &) override;
            void clear() override;
            std::vector<std::unique_ptr<IEvent>> const &getEvent(void) override;

            unsigned short getColor(int r, int g, int b);
            unsigned short getPair(unsigned short foreground, unsigned short background);

            void manageSingelObject(std::unique_ptr<IObject> const &object);

        protected:
            unsigned short m_nb_colors;
            unsigned short m_nb_pairs;
            std::vector<std::unique_ptr<IEvent>> m_eventGlobal;
            std::map<std::array<unsigned short, 3>, unsigned short> m_colors;
            std::map<std::array<unsigned short, 2>, unsigned short> m_pairs;
            std::map<int, std::string> m_mapOfEvents;
    };
}

#endif /* !ARCADESFML_HPP_ */
