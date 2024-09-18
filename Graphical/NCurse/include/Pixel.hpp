/*
** EPITECH PROJECT, 2024
** NCurse
** File description:
** Pixel
*/

#include <ncurses.h>
#include <array>

#ifndef PIXEL_HPP_
    #define PIXEL_HPP_

class Pixel {
    public:
        Pixel(short background = COLOR_BLACK, short foreground = COLOR_WHITE, char c = ' ');
        ~Pixel();

        char getChar() const;
        std::array<short, 2> const &getPair() const;

        void setChar(char c);
        void setPair(short background, short foreground);
        void setBackground(short background);
        void setForeground(short foreground);

    protected:
        char m_c;
        std::array<short, 2> m_pair;
};

#endif /* !PIXEL_HPP_ */
