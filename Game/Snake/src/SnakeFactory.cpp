/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** SnakeFactory
*/

#include "SnakeFactory.hpp"
#include "AObject.hpp"

std::unique_ptr<arcade::IObject> SnakeFactory::createSnakeParts(std::string const &asset, char c, int x, int y) const
{
    return std::make_unique<arcade::AObject>(0, 0, 255, x, y, 1, 1, asset, c, arcade::Graphic);
}

std::unique_ptr<arcade::IObject> SnakeFactory::createSnakeHead(std::string const &asset, int x, int y) const
{
    return std::make_unique<arcade::AObject>(0, 255, 0, x, y, 1, 1, asset, 'O', arcade::Graphic);
}

std::unique_ptr<arcade::IObject> SnakeFactory::createFood(int x, int y) const
{
    return std::make_unique<arcade::AObject>(255, 0, 0, x, y, 1, 1, "./assets/snake/apple.png", '$', arcade::Graphic);
}

std::unique_ptr<arcade::IObject> SnakeFactory::createWall(int x, int y, int width, int height) const
{
    return std::make_unique<arcade::AObject>(155, 155, 155, x, y, width, height, "", '#', arcade::Graphic);
}
