/*
** EPITECH PROJECT, 2024
** ArcadeSdl2
** File description:
** ArcadeSdl2
*/

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <exception>
#include <iostream>
#include <memory>
#include <vector>
#include "ArcadeSdl2.hpp"
#include "SDLTexture.hpp"
#include "AEvent.hpp"

arcade::ArcadeSdl2::ArcadeSdl2() : m_window(nullptr), m_renderer(nullptr),
                                    m_backgroundTexture(nullptr),
                                    m_runningFont(nullptr), m_windowHeight(1080), m_windowWidth(1920)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        throw std::runtime_error("Failed to initialize SDL: " + std::string(SDL_GetError()));
    }

    if (TTF_Init() != 0) {
        SDL_Quit();
        throw std::runtime_error("Failed to initialize SDL_ttf: " + std::string(TTF_GetError()));
    }

    m_window = SDL_CreateWindow("SDL2 Arcade", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_SHOWN);
    if (m_window == nullptr) {
        throw std::runtime_error("Failed to create SDL window: " + std::string(SDL_GetError()));
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (m_renderer == nullptr) {
        SDL_DestroyWindow(m_window);
        throw std::runtime_error("Failed to create SDL renderer: " + std::string(SDL_GetError()));
    }

    SDL_Surface *backgroundSurface = IMG_Load("assets/background.png");
    if (backgroundSurface == nullptr) {
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);
        TTF_Quit();
        SDL_Quit();
        throw std::runtime_error("Failed to load background: " + std::string(IMG_GetError()));
    }

    m_backgroundTexture = SDL_CreateTextureFromSurface(m_renderer, backgroundSurface);
    if (m_backgroundTexture == nullptr) {
        SDL_FreeSurface(backgroundSurface);
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);
        TTF_Quit();
        SDL_Quit();
        throw std::runtime_error("Failed to create texture from background: " + std::string(SDL_GetError()));
    }
    
    SDL_FreeSurface(backgroundSurface);

    m_mapOfEvents = {
        {SDLK_a, "A"},
        {SDLK_b, "B"},
        {SDLK_c, "C"},
        {SDLK_d, "D"},
        {SDLK_e, "E"},
        {SDLK_f, "F"},
        {SDLK_g, "G"},
        {SDLK_h, "H"},
        {SDLK_i, "I"},
        {SDLK_j, "J"},
        {SDLK_k, "K"},
        {SDLK_l, "L"},
        {SDLK_m, "M"},
        {SDLK_n, "N"},
        {SDLK_o, "O"},
        {SDLK_p, "P"},
        {SDLK_q, "Q"},
        {SDLK_r, "R"},
        {SDLK_s, "S"},
        {SDLK_t, "T"},
        {SDLK_u, "U"},
        {SDLK_v, "V"},
        {SDLK_w, "W"},
        {SDLK_x, "X"},
        {SDLK_y, "Y"},
        {SDLK_z, "Z"},
        {SDLK_TAB, "Switch"},
        {SDLK_UP, "Up"},
        {SDLK_DOWN, "Down"},
        {SDLK_LEFT, "Left"},
        {SDLK_RIGHT, "Right"},
        {SDLK_ESCAPE, "Escape"},
        {SDLK_RETURN, "Enter"},
        {SDLK_BACKSPACE, "Back Space"},
        {SDLK_DELETE, "Quit"},
    };

    m_manageFunc = {
        {arcade::Type::Text, &ArcadeSdl2::manageText},
        {arcade::Type::Graphic, &ArcadeSdl2::manageGraphical},
    };
    this->setFont("assets/pok.ttf");
}

arcade::ArcadeSdl2::~ArcadeSdl2()
{
    m_fontMap.clear();
    m_textureMap.clear();
    m_files.clear();

    if (m_backgroundTexture != nullptr) {
        SDL_DestroyTexture(m_backgroundTexture);
        m_backgroundTexture = nullptr;
    }

    if (m_renderer != nullptr) {
        SDL_DestroyRenderer(m_renderer);
        m_renderer = nullptr;
    }

    if (m_window != nullptr) {
        SDL_DestroyWindow(m_window);
        m_window = nullptr;
    }
    TTF_Quit();
    SDL_Quit();
}

void arcade::ArcadeSdl2::setFont(std::string const &path)
{
    if (path.empty()) {
        return;
    }

    auto finder = m_fontMap.find(path);
    if (finder != m_fontMap.end()) {
        m_runningFont = m_fontMap.at(path)->getFont();
    } else {
        std::shared_ptr<MySDL::SDLFont> new_font = std::make_shared<MySDL::SDLFont>();
        if (new_font->loadFromFile(path)) {
            m_fontMap.insert({path, new_font});
            m_runningFont = m_fontMap.at(path)->getFont();
            m_files.insert({path, true});
        } else {
            m_files.insert({path, false});
        }
    }
}

void arcade::ArcadeSdl2::clear()
{
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);
}

void arcade::ArcadeSdl2::setTexture(const std::string &asset, SDL_Color const &color)
{
    if (asset.empty()) {
        SDL_RenderFillRect(m_renderer, &m_rect);
        return;
    }

    auto finder1 = m_files.find(asset);
    if (finder1 != m_files.end()) {
        if (finder1->second == false) {
            SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
            SDL_RenderFillRect(m_renderer, &m_rect);
            return;
        }
    }

    auto finder = m_textureMap.find(asset);
    if (finder == m_textureMap.end()) {
        std::shared_ptr<MySDL::SDLTexture> new_texture = std::make_shared<MySDL::SDLTexture>();
        if (new_texture->loadFromFile(asset, m_renderer) == false) {
            std::cerr << "Error loading texture: " << IMG_GetError() << std::endl;
            m_files.insert({asset, false});
            return;
        }
        m_textureMap.insert({asset, new_texture});
        SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
        m_files.insert({asset, true});
    } else {
        SDL_RenderCopy(m_renderer, finder->second->getTexture(), NULL, &m_rect);
    }
}

void arcade::ArcadeSdl2::manageText(std::unique_ptr<IObject> const &object, int min, int windowCenterX, int windowCenterY)
{
    SDL_Surface *textSurface = nullptr;
    if (m_runningFont == nullptr) {
        return;
    }
    textSurface = TTF_RenderText_Solid(m_runningFont, object->getAsset().c_str(),
        {static_cast<Uint8>(object->getRGB()[0]), static_cast<Uint8>(object->getRGB()[1]), static_cast<Uint8>(object->getRGB()[2]),
            255});
    if (textSurface != nullptr) {
        SDL_Texture *textTexture = SDL_CreateTextureFromSurface(m_renderer, textSurface);
        SDL_FreeSurface(textSurface);
        SDL_Rect textRect;
        textRect.x = object->getPos()[0] * min + windowCenterX;
        textRect.y = object->getPos()[1] * min + windowCenterY;
        SDL_QueryTexture(textTexture, nullptr, nullptr, &textRect.w, &textRect.h);
        textRect.h *= object->getSize()[1];
        textRect.w *= object->getSize()[1];
        SDL_RenderCopy(m_renderer, textTexture, nullptr, &textRect);
        SDL_DestroyTexture(textTexture);
        textTexture = nullptr;
    }
}

void arcade::ArcadeSdl2::manageGraphical(std::unique_ptr<IObject> const &object, int min, int windowCenterX, int windowCenterY)
{
    m_rect.x = object->getPos()[0] * min + windowCenterX;
    m_rect.y = object->getPos()[1] * min + windowCenterY;
    m_rect.w = object->getSize()[0] * min;
    m_rect.h = object->getSize()[1] * min;

    SDL_SetRenderDrawColor(m_renderer, object->getRGB()[0], object->getRGB()[1], object->getRGB()[2], 255);
    setTexture(object->getAsset(), {static_cast<Uint8>(object->getRGB()[0]),
        static_cast<Uint8>(object->getRGB()[1]),
        static_cast<Uint8>(object->getRGB()[2]),
        255});
}

void arcade::ArcadeSdl2::display(data_t const &objects)
{
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);

    SDL_RenderCopy(m_renderer, m_backgroundTexture, nullptr, nullptr);

    int scaleX = (objects.size.first == 0) ? 25 : static_cast<int>(m_windowWidth) / objects.size.first;
    int scaleY = (objects.size.second == 0) ? 25 : static_cast<int>(m_windowHeight) / objects.size.second;

    int min = std::min(scaleX, scaleY);
    if (min > 25)
        min = 25;
    int windowCenterX = m_windowWidth / 2;
    int windowCenterY = m_windowHeight / 2;
    windowCenterX -= (objects.size.first * min) / 2;
    windowCenterY -= (objects.size.second * min) / 2;

    int squareCenterX = m_windowWidth / 2;
    int squareCenterY = m_windowHeight / 2;
    int squareWidth = objects.size.first * min;
    int squareHeight = objects.size.second * min;
    SDL_Rect blackSquare = {squareCenterX - squareWidth / 2, squareCenterY - squareHeight / 2, squareWidth, squareHeight};

    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(m_renderer, &blackSquare);

    for (auto it = objects.objects.begin(); it != objects.objects.end(); ++it) {
        auto fct = m_manageFunc.find((*it)->getType());
        if (fct != m_manageFunc.end()) {
            fct->second(*this, *it, min, windowCenterX, windowCenterY);
        }
    }
    SDL_RenderPresent(m_renderer);
}

std::vector<std::unique_ptr<arcade::IEvent>> const &arcade::ArcadeSdl2::getEvent(void)
{
    m_eventGlobal.clear();

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN) {
            auto it = m_mapOfEvents.find(event.key.keysym.sym);
            if (it != m_mapOfEvents.end()) {
                m_eventGlobal.push_back(std::make_unique<AEvent>((*it).second));
            }
        } else if (event.type == SDL_QUIT) {
            m_eventGlobal.push_back(std::make_unique<AEvent>("Quit"));
        }
    }
    return (m_eventGlobal);
}
