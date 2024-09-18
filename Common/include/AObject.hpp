/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** AObject
*/

#include "Arcade.hpp"

#ifndef AOBJECT_HPP_
    #define AOBJECT_HPP_

namespace arcade {
    class AObject : public IObject {
        public:
            AObject(int r, int g, int b, int x, int y, int width, int height, std::string const &asset, char c, arcade::Type type);
            ~AObject() = default;
            std::array<int, 3> const &getRGB(void) const override;
            std::array<int, 2> const &getPos(void) const override;
            std::array<int, 2> const &getSize(void) const override;
            std::string const &getAsset(void) const override;
            char getAscii(void) const override;
            Type getType(void) const override;

        protected:
            std::array<int, 3> m_color;
            std::array<int, 2> m_pos;
            std::array<int, 2> m_size;
            std::string m_asset;
            char m_char;
            Type m_type;
    };
}

#endif /* !AOBJECT_HPP_ */
