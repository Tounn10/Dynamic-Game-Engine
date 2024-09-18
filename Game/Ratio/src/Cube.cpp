/*
** EPITECH PROJECT, 2024
** Game
** File description:
** Cube
*/

#include "Cube.hpp"
#include <cmath>
#include <cfloat>

Cube::Cube(std::array<double, 3> pos, std::array<double, 3> size) :
m_pos(pos), m_size(size)
{}

Cube::~Cube()
{}

std::array<double, 3> const &Cube::getPos() const
{
    return m_pos;
}

std::array<double, 3> const &Cube::getSize() const
{
    return m_size;
}

bool Cube::fillCollisionPoint(const Ray& ray, std::array<double, 3> &collisionPoint) const
{
    std::array<double, 3> ray_origin = ray.getStart();
    std::array<double, 3> ray_direction = ray.getDirection();

    // Paramètres du rayon pour l'intersection avec les plans du cube
    double t_near = -DBL_MAX;
    double t_far = DBL_MAX;

    for (int i = 0; i < 3; ++i) {
        if (ray_direction[i] != 0.0) {
            double t1 = (m_pos[i] - ray_origin[i]) / ray_direction[i];
            double t2 = (m_pos[i] + m_size[i] - ray_origin[i]) / ray_direction[i];
            double t_min = std::min(t1, t2);
            double t_max = std::max(t1, t2);

            t_near = std::max(t_near, t_min);
            t_far = std::min(t_far, t_max);
        } else {
            if (ray_origin[i] < m_pos[i] || ray_origin[i] > m_pos[i] + m_size[i])
                return false;
        }
    }

    // Vérifier si le point d'intersection est à l'intérieur du cube
    if (t_near > t_far || t_far < 0)
        return false;

    // Calculer le point d'intersection
    for (int i = 0; i < 3; ++i) {
        collisionPoint[i] = ray_origin[i] + t_near * ray_direction[i];
    }

    return true;
}
