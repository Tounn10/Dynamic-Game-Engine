/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** SDLTexture
*/

#include "SDLTexture.hpp"

MySDL::SDLTexture::SDLTexture():
m_texture(nullptr)
{}

SDL_Texture *MySDL::SDLTexture::getTexture() const
{
    return m_texture;
}

MySDL::SDLTexture::~SDLTexture()
{
    if (m_texture != nullptr) {
        SDL_DestroyTexture(m_texture);
    }
}

bool MySDL::SDLTexture::loadFromFile(std::string const &path, SDL_Renderer *renderer)
{
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == nullptr) {
        std::cout << "Erreur lors du chargement de l'image " << path  << ": " << IMG_GetError() << std::endl;
        return false;
    }
    m_texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if(m_texture == nullptr) {
        std::cout << "Erreur lors de la création de la texture pour" << path << ": " << SDL_GetError() << std::endl;
        return NULL;
    }
    SDL_FreeSurface(loadedSurface);
    return true;
}
