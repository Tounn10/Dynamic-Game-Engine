/*
** EPITECH PROJECT, 2024
** Game
** File description:
** Cube
*/

#include <array>
#include "Ray.hpp"

#ifndef CUBE_HPP_
    #define CUBE_HPP_

class Cube {
    public:
        Cube(std::array<double, 3>, std::array<double, 3>);
        ~Cube();

        std::array<double, 3>const &getPos() const;
        std::array<double, 3>const &getSize() const;

        bool fillCollisionPoint(const Ray& ray, std::array<double, 3> &collisionPoint) const;

    protected:
        std::array<double, 3> m_pos;
        std::array<double, 3> m_size;
};

#endif /* !CUBE_HPP_ */
