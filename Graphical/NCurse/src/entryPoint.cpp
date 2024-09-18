/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** entryPoint
*/

#include <memory>
#include "ArcadeNcurses.hpp"
// #include "Common/Arcade.hpp"

extern "C" std::unique_ptr<arcade::IDisplayModule> entryPoint()
{
    return std::make_unique<arcade::ArcadeNcurses>();
}
