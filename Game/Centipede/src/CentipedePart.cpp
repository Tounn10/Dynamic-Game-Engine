/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** CentipedePart
*/

#include "CentipedePart.hpp"
#include <iostream>

arcade::CentipedePart::CentipedePart(int x, int y, CentipedePartDirection dir) :
m_direction(dir)
{
    m_part = {x, y};
}

bool arcade::CentipedePart::touchedBy(std::array<int, 2> pos)
{
    if (m_part[0] == pos[0] && m_part[1] == pos[1]) {
        return true;
    }
    return false;
}

arcade::CentipedePartDirection arcade::CentipedePart::getDirection(void) const
{
    return m_direction;
}

void arcade::CentipedePart::collideWall(void)
{
    if (m_direction == Left) {
        m_part[0] += 1;
        m_part[1] += 1;
        m_direction = Right;
    } else if (m_direction == Right) {
        m_part[0] -= 1;
        m_part[1] += 1;
        m_direction = Left;
    }
}

std::array<int, 2> const &arcade::CentipedePart::getBody(void) const
{
    return m_part;
}

void arcade::CentipedePart::move()
{
    if (m_direction == Left) {
        m_part[0] -= 1;
    }
    if (m_direction == Right) {
        m_part[0] += 1;
    }
}
