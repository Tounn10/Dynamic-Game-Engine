/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** Snake
*/

#include "Arcade.hpp"
#include <array>
#include <chrono>
#include <vector>
#include "Cube.hpp"
#include "Ray.hpp"

#ifndef SNAKE_HPP_
    #define SNAKE_HPP_

namespace arcade {
    class RatioGame : public IGameModule {
        public:
            RatioGame();
            ~RatioGame();
            void manageEvent(std::vector<std::unique_ptr<IEvent>> const &events) override;
            void iterate(void) override;
            data_t const &getMap(void) const override;

            double computeSingleRay(Ray const &ray) const;
            double computeDistance(std::array<double, 3> const &pos1, std::array<double, 3> const &pos2) const;

        protected:
            size_t m_nb_walls;
            int m_height;
            int m_width;
            data_t m_object;
            std::chrono::high_resolution_clock::time_point m_last_time;
            std::chrono::duration<double> m_speed;
            std::vector<Cube> m_cubes;
            Ray m_ray;

    };
}


#endif /* !SNAKE_HPP_ */
