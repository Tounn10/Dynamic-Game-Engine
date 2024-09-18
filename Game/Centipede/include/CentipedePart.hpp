/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** CentipedePart
*/

#include <list>
#include <array>
#include <functional>

#pragma once

namespace arcade {
    enum CentipedePartDirection {
        Right,
        Left,
        Up,
        Down,
        NoDir
    };

    class CentipedePart {
        public:
            ~CentipedePart() = default;
            CentipedePart(int x, int y, CentipedePartDirection dir);

            std::array<int, 2> const &getBody(void) const;
            void move();

            void collideWall(void);
            bool touchedBy(std::array<int, 2> pos);

            CentipedePartDirection getDirection(void) const;

        protected:
            CentipedePartDirection m_direction;
            std::array<int, 2> m_part;

    };
}
