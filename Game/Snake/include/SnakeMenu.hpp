/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** SnakeMenu
*/

#include "Arcade.hpp"

#ifndef SNAKEMENU_HPP_
    #define SNAKEMENU_HPP_

class SnakeMenu : public arcade::IGameModule {
    public:
        SnakeMenu();
        ~SnakeMenu() = default;

        void manageEvent(std::vector<std::unique_ptr<arcade::IEvent>> const &events) override;
        void iterate(void) override;
        arcade::data_t const &getMap(void) const override;

        bool isRunning() const;
        void setMenuRunning(bool running);

    private:
        bool m_menuRunning;
        arcade::data_t m_data;
};

#endif /* !SNAKEMENU_HPP_ */
