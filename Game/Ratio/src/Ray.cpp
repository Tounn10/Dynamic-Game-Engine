/*
** EPITECH PROJECT, 2024
** Game
** File description:
** Ray
*/

#include "Ray.hpp"
#include <cmath>

Ray::Ray(std::array<double, 3> src, double horizontalAngle, double verticalAngle) :
m_start(src), m_horizontalAngle(horizontalAngle), m_verticalAngle(verticalAngle)
{}

Ray::~Ray()
{}

std::array<double, 3> const &Ray::getStart() const
{
    return m_start;
}

void Ray::setStart(std::array<double, 3> const &newStart)
{
    m_start = newStart;
}

std::array<double, 3> Ray::getDirection() const
{
    double x = cos(m_horizontalAngle) * cos(m_verticalAngle);
    double y = sin(m_horizontalAngle) * cos(m_verticalAngle);
    double z = sin(m_verticalAngle);

    x = round(x * 1000.0) / 1000.0;
    y = round(y * 1000.0) / 1000.0;
    z = round(z * 1000.0) / 1000.0;

    // Retourner les coordonnées du vecteur sous forme de tuple
    return {x, y, z};
}

void Ray::setDirection(std::array<double, 3> const &newDirection)
{
    m_horizontalAngle = std::atan2(newDirection[1], newDirection[0]);
    m_verticalAngle = std::atan2(newDirection[2], std::sqrt(newDirection[0] * newDirection[0] + newDirection[1] * newDirection[1]));
}

void Ray::move(double delta)
{
    std::array<double, 3> direction = getDirection();
    std::array<double, 3> newStart = {m_start[0] + direction[0] * delta,
                                      m_start[1] + direction[1] * delta,
                                      m_start[2] + direction[2] * delta};
    setStart(newStart);
}

void Ray::turnHorizontally(double delta)
{
    m_horizontalAngle += delta;
}

void Ray::turnVertically(double delta)
{
    m_verticalAngle += delta;
}

bool Ray::operator==(Ray const &other) const
{
    return m_start == other.m_start
        && m_horizontalAngle == other.m_horizontalAngle
        && m_verticalAngle == other.m_verticalAngle;
}
