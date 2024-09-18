/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** Snake
*/

#include "Snake.hpp"
#include "SnakeMenu.hpp"
#include "Arcade.hpp"
#include "SnakeFactory.hpp"
#include <array>
#include <chrono>
#include <list>

#ifndef SNAKEGAME_HPP_
    #define SNAKEGAME_HPP_

namespace arcade {
    class SnakeGame : public IGameModule {
        public:
            SnakeGame();
            ~SnakeGame();
            void manageEvent(std::vector<std::unique_ptr<IEvent>> const &events) override;
            void iterate(void) override;
            data_t const &getMap(void) const override;

            bool hasLost(void);
            void manageApple(void);

        protected:
            size_t m_nb_walls;
            Snake m_snake;
            int m_height;
            int m_width;
            data_t m_object;
            std::array<int, 2> m_apple;
            std::chrono::high_resolution_clock::time_point m_last_time;
            std::chrono::duration<double> m_speed;
            std::list<SnakeDirection> m_directions;

            SnakeMenu m_snakeMenu;

            SnakeFactory m_factory;
    };
}


#endif /* !SNAKEGAME_HPP_ */
