/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** SDLTexture
*/

#include <iostream>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>

#ifndef SDLTEXTURE_HPP_
    #define SDLTEXTURE_HPP_

namespace MySDL {
    class SDLTexture {
        public:
            SDLTexture();
            ~SDLTexture();
            
            bool loadFromFile(std::string const &path, SDL_Renderer *renderer);
            SDL_Texture *getTexture() const;


        protected:
            SDL_Texture *m_texture;
    };
}

#endif /* !SDLTEXTURE_HPP_ */
