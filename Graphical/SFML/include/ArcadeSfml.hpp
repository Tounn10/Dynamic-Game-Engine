/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** ArcadeSfml
*/

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <map>
#include <functional>

#include "Arcade.hpp"

#ifndef ARCADESFML_HPP_
    #define ARCADESFML_HPP_

namespace arcade {
    class ArcadeSfml : public arcade::IDisplayModule {
        public:
            ArcadeSfml();
            ~ArcadeSfml();
            void display(data_t const &) override;
            void clear() override;
            std::vector<std::unique_ptr<IEvent>> const &getEvent(void) override;

            void setTexture(const std::string &name, sf::Color const &);

            void manageText(std::unique_ptr<IObject> const &object, int min, int windowCenterX, int windowCenterY);
            void manageGraphical(std::unique_ptr<IObject> const &object, int min, int windowCenterX, int windowCenterY);
            void manageFont(std::unique_ptr<IObject> const &object, int min, int windowCenterX, int windowCenterY);

            void setFont(std::string const &path);

        protected:
            std::vector<std::unique_ptr<IEvent>> m_eventGlobal;
            std::map<sf::Keyboard::Key, std::string> m_mapOfEvents;
            sf::RenderWindow m_window;
            sf::RectangleShape m_rect;
            sf::Text m_text;
            sf::Event m_event;
            sf::Texture m_backgroundTexture;
            sf::Sprite m_backgroundSprite;
            int originalWidth = 1920;
            int originalHeight = 1080;

            std::map<std::string, sf::Texture> m_textureMap;
            std::map<std::string, sf::Font> m_fontMap;
            std::map<std::string, bool> m_files;


            std::map<arcade::Type, std::function<void(ArcadeSfml &, std::unique_ptr<IObject> const &, int, int, int)>> m_manageFunc;
    };
}

#endif /* !ARCADESFML_HPP_ */
