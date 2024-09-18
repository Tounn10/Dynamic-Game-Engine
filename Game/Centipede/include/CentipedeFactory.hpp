/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** CentipedeFactory
*/

#include <memory>
#include "Arcade.hpp"

#ifndef CENTIPEDEFACTORY_HPP_
    #define CENTIPEDEFACTORY_HPP_

class CentipedeFactory {
    public:
        std::unique_ptr<arcade::IObject> createPart(std::string const &asset, int x, int y);
        std::unique_ptr<arcade::IObject> createPlayer(int x, int y);
        std::unique_ptr<arcade::IObject> createShot(int x, int y);
        std::unique_ptr<arcade::IObject> createWall(int x, int y);
};

#endif /* !CENTIPEDEFACTORY_HPP_ */
