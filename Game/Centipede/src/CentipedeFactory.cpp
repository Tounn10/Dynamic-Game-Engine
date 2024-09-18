/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** CentipedeFactory
*/

#include "CentipedeFactory.hpp"
#include "AObject.hpp"

std::unique_ptr<arcade::IObject> CentipedeFactory::createPart(std::string const &asset, int x, int y)
{
    return std::make_unique<arcade::AObject>(255, 165, 0, x, y, 1, 1, asset, 'O', arcade::Graphic);
}

std::unique_ptr<arcade::IObject> CentipedeFactory::createPlayer(int x, int y)
{
    return std::make_unique<arcade::AObject>(0, 255, 0, x, y, 1, 1, "./assets/centipede/player.png", 'P', arcade::Graphic);
}

std::unique_ptr<arcade::IObject> CentipedeFactory::createShot(int x, int y)
{
    return std::make_unique<arcade::AObject>(255, 0, 0, x, y, 1, 1, "./assets/centipede/fire.png", '*', arcade::Graphic);
}

std::unique_ptr<arcade::IObject> CentipedeFactory::createWall(int x, int y)
{
    return std::make_unique<arcade::AObject>(0, 0, 255, x, y, 1, 1, "./assets/centipede/wall.png", '#', arcade::Graphic);
}
