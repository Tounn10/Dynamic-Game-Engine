/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** Snake
*/

#include "CentipedeGame.hpp"
#include "AObject.hpp"
#include <fstream>
#include <memory>
#include <sstream>
#include <ctime>
#include <cstdlib>

extern "C" std::unique_ptr<arcade::IGameModule> entryPoint()
{
    return std::make_unique<arcade::CentipedeGame>();
}

arcade::CentipedeGame::CentipedeGame() :
m_playerCd(1), m_timeToRecharge(1), m_wallLife(5),
m_isGameOver(true), m_nbCentipedesLeft(0), hasMoved(false),
m_last_time(std::chrono::high_resolution_clock::now())
{
    m_data.size = {32, 48};

    std::srand(std::time(nullptr));
    this->setStartMenu();
}

void arcade::CentipedeGame::manageEvent(std::vector<std::unique_ptr<arcade::IEvent>> const &events)
{
    if (events.size() == 0) {
        return;
    }
    if (m_isGameOver == true) {
        m_isGameOver = false;
        reset();
        return;
    }
    for (auto it = events.begin(); it != events.end(); ++it) {
        std::string const &type = (*it)->type();

        if (type == "Down" && m_playerPos[1] < m_data.size.second - 1) {
            m_playerPos[1]++;
        }
        if (type == "Left" && m_playerPos[0] > 0) {
            m_playerPos[0]--;
        }
        if (type == "Up" && m_playerPos[1] > (80  * m_data.size.second / 100)) {
            m_playerPos[1]--;
        }
        if (type == "Right" && m_playerPos[0] < m_data.size.first - 1) {
            m_playerPos[0]++;
        }
        if (type == "A" && m_playerCd == m_timeToRecharge && m_shots.size() == 0) {
            m_shots.push_back(m_playerPos);
            m_playerCd = 0;
        }
    }
    return;
}

bool arcade::CentipedeGame::hasLost(void)
{
    for (auto it = m_centipedes.begin(); it != m_centipedes.end(); it++) {
        if (it->getBody()[0] == m_playerPos[0] && it->getBody()[1] == m_playerPos[1]) {
            return true;
        }
        if (it->getBody()[1] >= m_data.size.second) {
            return true;
        }
    }
    return false;
}

void arcade::CentipedeGame::setStartMenu(void)
{
    std::string title = "Centipede";
    std::string text = "Press any key to start";
    m_data.objects.clear();
    m_data.objects.push_back(std::make_unique<AObject>(255, 255, 255, 1, 0, 1, 2, title, ' ', arcade::Text));
    m_data.objects.push_back(std::make_unique<AObject>(255, 255, 255, 1, 2, 1, 1, text, ' ', arcade::Text));
    m_data.size = {text.length(), 3};
    m_isGameOver = true;
}

void arcade::CentipedeGame::setEndMenu(void)
{
    std::string title = (m_nbCentipedesLeft == 0 && m_centipedes.size() == 0) ? "You win !" : "You lost !";
    std::string text = "Press any key to start";
    m_data.objects.clear();
    m_data.objects.push_back(std::make_unique<AObject>(0, 0, 0, 0, 0, 0, 0, "./assets/title.ttf", ' ', arcade::Font));
    m_data.objects.push_back(std::make_unique<AObject>(255, 255, 255, 1, 0, 1, 2, title, ' ', arcade::Text));
    m_data.objects.push_back(std::make_unique<AObject>(0, 0, 0, 0, 0, 0, 0, "./assets/pok.ttf", ' ', arcade::Font));
    m_data.objects.push_back(std::make_unique<AObject>(255, 255, 255, 1, 2, 1, 1, text, ' ', arcade::Text));
    m_data.size = {text.length(), 3};
    m_isGameOver = true;
}

void arcade::CentipedeGame::reset(void)
{
    m_centipedes.clear();
    m_data.size = {16, 32};
    m_playerPos = {m_data.size.first / 2, (m_data.size.second * 90) / 100};
    m_shots.clear();
    m_playerCd = 0;
    m_walls.clear();
    m_nbCentipedesLeft = 20;

    int y_max = ((80  * m_data.size.second) / 100) - 2;
    int x_max = m_data.size.first - 2;

    m_isGameOver = false;
    size_t nb_walls = rand() % 15 + 15;
    for (size_t i = 0; i < nb_walls; i++) {
        int x = rand() % x_max + 1;
        int y = rand() % y_max + 1;
        m_walls[{x, y}] = m_wallLife;
    }
    return;
}

void arcade::CentipedeGame::managePlayerShots(void)
{
    std::vector<std::vector<std::array<int, 2>>::iterator> shots_to_delete;

    auto it = m_shots.begin();
    while (it != m_shots.end()) {
        (*it)[1]--;

        auto it2 = m_centipedes.begin();
        while (it2 != m_centipedes.end()) {
            if (it2->getBody()[0] == (*it)[0] && it2->getBody()[1] == (*it)[1]) {
                it = m_shots.erase(it);
                m_walls.insert({it2->getBody(), m_wallLife});
                it2 = m_centipedes.erase(it2);
                continue;
            }
            it2++;
        }

        auto finder = m_walls.find(*it);
        if (finder != m_walls.end()) {
            damageWall(*it);
            it = m_shots.erase(it);
            continue;
        }

        if ((*it)[1] < 0) {
            it = m_shots.erase(it);
            continue;
        }
        m_data.objects.push_back(m_factory.createShot((*it)[0], (*it)[1]));
        it++;
    }
}

void arcade::CentipedeGame::damageWall(std::array<int, 2> const &pos)
{
    auto finder = m_walls.find(pos);
    if (finder != m_walls.end()) {
        finder->second--;
        if (finder->second <= 0) {
            m_walls.erase(finder);
        }
    }
}

void arcade::CentipedeGame::manageCentipedes(void)
{
    if (m_centipedes.size() == 0) {
        CentipedePartDirection dir = (rand() % 2 == 0) ? CentipedePartDirection::Right : CentipedePartDirection::Left;
        addCentipede({(dir == CentipedePartDirection::Left) ? (m_data.size.first - 1) : (0), 0}, dir, rand() % 3 + 3);
        return;
    }
    hasMoved = !hasMoved;
    
    bool hasCollided = false;
    for (auto it = m_centipedes.begin(); it != m_centipedes.end(); it++) {
        hasCollided = false;
        if (!hasMoved) {
            it->move();

            if (it->getDirection() == CentipedePartDirection::Right && it->getBody()[0] >= m_data.size.first) {
                it->collideWall();
                hasCollided = true;
            }
            if (it->getDirection() == CentipedePartDirection::Left && it->getBody()[0] < 0) {
                it->collideWall();
                hasCollided = true;
            }
            auto finder = m_walls.find(it->getBody());
            if (finder != m_walls.end()) {
                it->collideWall();
                hasCollided = true;
            }
        }
        
        std::string name = "assets/centipede/";
        if (hasCollided) {
            name += "body_down.png";
        } else {
            name += (it->getDirection() == CentipedePartDirection::Right) ? "body_right.png" : "body_left.png";
        }
        m_data.objects.push_back(m_factory.createPart(name, it->getBody()[0], it->getBody()[1]));
    }

}

void arcade::CentipedeGame::addCentipede(std::array<int, 2> const &posHead, CentipedePartDirection dir, size_t len)
{
    if (dir == CentipedePartDirection::Right) {
        for (size_t i = 0; i < len; i++) {
            m_centipedes.emplace_back(posHead[0] - i, posHead[1], dir);
        }
    } else {
        for (size_t i = 0; i < len; i++) {
            m_centipedes.emplace_back(posHead[0] + i, posHead[1], dir);
        }
    }
    m_nbCentipedesLeft -= 1;
}

void arcade::CentipedeGame::iterate(void)
{
    auto current = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_elapsed = current - m_last_time;
    if (time_elapsed.count() < 0.05) {
        return;
    }
    m_last_time = current;

    if (m_isGameOver) {
        return;
    }
    if ((hasLost() || m_nbCentipedesLeft == 0)) {
        this->setEndMenu();
        return;
    }

    if (m_playerCd < m_timeToRecharge)
        m_playerCd++;
    m_data.objects.clear();
    managePlayerShots();
    manageCentipedes();
    for (auto it = m_walls.begin(); it != m_walls.end(); it++) {
        m_data.objects.push_back(m_factory.createWall(it->first[0], it->first[1]));
    }
    m_data.objects.push_back(m_factory.createPlayer(m_playerPos[0], m_playerPos[1]));
    return;
}

arcade::data_t const &arcade::CentipedeGame::getMap(void) const
{
    return m_data;
}

arcade::CentipedeGame::~CentipedeGame()
{}
