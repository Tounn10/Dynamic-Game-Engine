/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** Snake
*/

#include <list>
#include <array>
#include <map>
#include "Arcade.hpp"
#include "SnakeFactory.hpp"

#ifndef SNAKE_HPP_
    #define SNAKE_HPP_

namespace arcade {
    enum SnakeDirection {
        Right,
        Up,
        Left,
        Down,
        NoDir
    };

    class Snake {
        public:
            Snake(int x, int y);
            std::list<std::array<int, 2>> const &getTail(void) const;
            void move(SnakeDirection dir);
            bool isTouchingItsOwnTail(void) const;
            void addElem(void);
            void reset(int x, int y);
            bool isAPartOf(std::array<int, 2> const &elem) const;
            void toObject(arcade::data_t &object, SnakeFactory const &factory) const;

            char getAscii(std::list<std::array<int, 2>>::const_iterator const &it) const;
            std::string getAsset(std::list<std::array<int, 2>>::const_iterator const &it) const;

            SnakeDirection getDirectionPart(std::list<std::array<int, 2>>::const_iterator const &it) const;
            std::string dirToString(SnakeDirection dir) const;
        protected:
            std::list<std::array<int, 2>> m_snake;
            SnakeDirection m_direction;
            bool hasGrown;
    };
}

#endif /* !SNAKE_HPP_ */
