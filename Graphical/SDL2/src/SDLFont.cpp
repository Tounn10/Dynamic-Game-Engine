/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** SDLFont
*/

#include "SDLFont.hpp"

MySDL::SDLFont::SDLFont()
{
    m_font = nullptr;
}

MySDL::SDLFont::~SDLFont()
{
    if (m_font != nullptr) {
        TTF_CloseFont(m_font);
        m_font = nullptr;
    }
}

bool MySDL::SDLFont::loadFromFile(std::string const &path)
{
    m_font = TTF_OpenFont(path.c_str(), 25);
    if (m_font == nullptr) {
        return false;
    }
    return true;
}

TTF_Font *MySDL::SDLFont::getFont() const
{
    return m_font;
}
