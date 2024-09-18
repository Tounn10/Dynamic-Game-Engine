/*
** EPITECH PROJECT, 2024
** ArcadeSdl2
** File description:
** ArcadeSdl2
*/

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <map>
#include <memory>
#include <functional>

#include "Arcade.hpp"
#include "SDLTexture.hpp"
#include "SDLFont.hpp"

#ifndef ARCADESDL2_HPP_
    #define ARCADESDL2_HPP_

namespace arcade {
    class ArcadeSdl2 : public arcade::IDisplayModule {
        public:
            ArcadeSdl2();
            ~ArcadeSdl2();
            void display(data_t const &) override;
            void clear() override;
            std::vector<std::unique_ptr<IEvent>> const &getEvent(void) override;

            void manageText(std::unique_ptr<IObject> const &object, int min, int windowCenterX, int windowCenterY);
            void manageGraphical(std::unique_ptr<IObject> const &object, int min, int windowCenterX, int windowCenterY);
            void manageFont(std::unique_ptr<IObject> const &object, int min, int windowCenterX, int windowCenterY);

            void setFont(std::string const &path);

            void setTexture(const std::string &asset, SDL_Color const &);
        protected:
            std::vector<std::unique_ptr<IEvent>> m_eventGlobal;
            std::map<SDL_Keycode, std::string> m_mapOfEvents;
            SDL_Window *m_window;
            SDL_Renderer *m_renderer;
            SDL_Rect m_rect;
            SDL_Texture *m_backgroundTexture;
            SDL_Event m_event;
            SDL_Rect m_backgroundRect;
            TTF_Font *m_runningFont;

            std::map<std::string, std::shared_ptr<MySDL::SDLTexture>> m_textureMap;
            std::map<std::string, std::shared_ptr<MySDL::SDLFont>> m_fontMap;
            std::map<std::string, bool> m_files;

            size_t m_windowHeight;
            size_t m_windowWidth;
            std::map<arcade::Type, std::function<void(ArcadeSdl2 &, std::unique_ptr<IObject> const &, int, int, int)>> m_manageFunc;
    };
}

#endif
