/*
** EPITECH PROJECT, 2024
** entryPoint
** File description:
** entryPoint
*/

#include <memory>
#include "ArcadeSdl2.hpp"
#include "Arcade.hpp"

extern "C" std::unique_ptr<arcade::IDisplayModule> entryPoint()
{
    return std::make_unique<arcade::ArcadeSdl2>();
}
