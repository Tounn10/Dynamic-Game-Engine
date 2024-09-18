/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** SnakeFactory
*/

#include <memory>
#include "Arcade.hpp"

#ifndef SNAKEFACTORY_HPP_
    #define SNAKEFACTORY_HPP_

class SnakeFactory {
    public:
        std::unique_ptr<arcade::IObject> createSnakeParts(std::string const &asset, char c, int x, int y) const;
        std::unique_ptr<arcade::IObject> createSnakeHead(std::string const &asset, int x, int y) const;
        std::unique_ptr<arcade::IObject> createFood(int x, int y) const;
        std::unique_ptr<arcade::IObject> createWall(int x, int y, int width, int height) const;

    protected:
};

#endif /* !SNAKEFACTORY_HPP_ */
