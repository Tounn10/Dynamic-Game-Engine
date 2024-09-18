/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** SDLFont
*/

#include <SDL2/SDL_ttf.h>
#include <iostream>

#ifndef SDLFONT_HPP_
    #define SDLFONT_HPP_

namespace MySDL {
    class SDLFont {
        public:
            SDLFont();
            ~SDLFont();

            bool loadFromFile(std::string const &path);
            TTF_Font *getFont() const;


        private:
            TTF_Font *m_font;
    };
}

#endif /* !SDLFONT_HPP_ */
