/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** AObject
*/

#include "AObject.hpp"

arcade::AObject::AObject(int r, int g, int b, int x, int y, int width, int height, std::string const &asset, char c, arcade::Type type) :
m_color({r, g, b}), m_pos({x, y}), m_size({width, height}), m_asset(asset), m_char(c), m_type(type)
{}

std::array<int, 3> const & arcade::AObject::getRGB(void) const
{
    return m_color;
}

std::array<int, 2> const & arcade::AObject::getPos(void) const
{
    return m_pos;
}

std::array<int, 2> const & arcade::AObject::getSize(void) const
{
    return m_size;
}

std::string const & arcade::AObject::getAsset(void) const
{
    return m_asset;
}

char arcade::AObject::getAscii(void) const
{
    return m_char;
}

arcade::Type arcade::AObject::getType(void) const
{
    return m_type;
}
