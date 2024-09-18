/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** Centipede Game
*/

#include "CentipedePart.hpp"
#include "CentipedeFactory.hpp"
#include "Arcade.hpp"
#include <array>
#include <chrono>
#include <list>
#include <map>

#ifndef CENTIPEDE_HPP_
    #define CENTIPEDE_HPP_

namespace arcade {
    class CentipedeGame : public IGameModule {
        public:
            CentipedeGame();
            ~CentipedeGame();
            void manageEvent(std::vector<std::unique_ptr<IEvent>> const &events) override;
            void iterate(void) override;
            data_t const &getMap(void) const override;

            bool hasLost(void);
            void reset(void);
            void managePlayerShots(void);
            void manageCentipedes(void);
            void damageWall(std::array<int, 2> const &pos);

            void addCentipede(std::array<int, 2> const &posHead, CentipedePartDirection dir, size_t len);

            void setStartMenu(void);
            void setEndMenu(void);

        protected:
            std::list<arcade::CentipedePart> m_centipedes;

            std::array<int, 2> m_playerPos;
            std::list<std::array<int, 2>> m_shots;
            int m_playerCd;
            int m_timeToRecharge;
            std::map<std::array<int, 2>, int> m_walls;
            int m_wallLife;

            bool m_isGameOver;
            int m_nbCentipedesLeft;
            bool hasMoved;

            data_t m_data;
            std::chrono::high_resolution_clock::time_point m_last_time;
            std::chrono::duration<double> m_speed;
            CentipedeFactory m_factory;
    };
}


#endif /* !CENTIPEDE_HPP_ */
