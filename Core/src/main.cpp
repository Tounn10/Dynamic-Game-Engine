/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** main
*/

#include "Core.hpp"

int main(int ac, char **av) {
    if (ac != 2) {
        return 84;
    }
    arcade::Core core(av[1]);
    int ret = core.getExitValue();
    return ret;
}
