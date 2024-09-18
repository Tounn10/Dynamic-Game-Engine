/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** entryPoint
*/

#include <memory>
#include "ArcadeSfml.hpp"
#include "Arcade.hpp"

extern "C" std::unique_ptr<arcade::IDisplayModule> entryPoint()
{
    return std::make_unique<arcade::ArcadeSfml>();
}
