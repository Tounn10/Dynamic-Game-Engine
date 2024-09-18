/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** Snake
*/

#include "SnakeGame.hpp"
#include "AObject.hpp"
#include <fstream>
#include <memory>
#include <sstream>
#include <ctime>
#include <cstdlib>

extern "C" std::unique_ptr<arcade::IGameModule> entryPoint()
{
    return std::make_unique<arcade::SnakeGame>();
}

arcade::SnakeGame::SnakeGame() :
m_nb_walls(0), m_snake(10, 5),
m_height(16), m_width(40), m_apple({10, 7}),
m_last_time(std::chrono::high_resolution_clock::now())
{
    m_object.size = {m_width, m_height};
    std::srand(std::time(nullptr));
}

void arcade::SnakeGame::manageEvent(std::vector<std::unique_ptr<arcade::IEvent>> const &events)
{
    if (events.size() == 0) {
        return;
    }

    if (m_snakeMenu.isRunning()) {
        m_snakeMenu.manageEvent(events);
        if (m_snakeMenu.isRunning())
            return;
    }
    for (auto it = events.begin(); it != events.end(); ++it) {
        std::string const &type = (*it)->type();

        if (type == "Down")
            this->m_directions.push_back(Down);
        if (type == "Left")
            this->m_directions.push_back(Left);
        if (type == "Up")
            this->m_directions.push_back(Up);
        if (type == "Right")
            this->m_directions.push_back(Right);
    }
    return;
}

bool arcade::SnakeGame::hasLost(void)
{
    int xhead = m_snake.getTail().front()[0];
    int yhead = m_snake.getTail().front()[1];
    size_t surface = static_cast<size_t>(m_width * m_height);

    if (m_snake.isTouchingItsOwnTail() || m_snake.getTail().size() >= surface) {
        return true;
    }
    if (xhead <= 0 || xhead >= m_width
        || yhead <= 0 || yhead >= m_height) {
            return true;
        }
    return false;
}

void arcade::SnakeGame::manageApple(void)
{
    int xhead = m_snake.getTail().front()[0];
    int yhead = m_snake.getTail().front()[1];

    if (hasLost()) {
        return;
    }
    if (xhead == m_apple[0] && yhead == m_apple[1]) {
        m_snake.addElem();
        m_apple[0] = (rand() % (m_width - 2)) + 1;
        m_apple[1] = (rand() % (m_height - 2)) + 1;
        while (m_snake.isAPartOf(m_apple)) {
            m_apple[0] = (rand() % (m_width - 2)) + 1;
            m_apple[1] = (rand() % (m_height - 2)) + 1;
        }
    }
}

void arcade::SnakeGame::iterate(void)
{
    if (m_snakeMenu.isRunning()) {
        m_snakeMenu.iterate();
        return;
    }

    auto current = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_elapsed = current - m_last_time;
    if (time_elapsed.count() < 0.10) {
        return;
    }
    m_last_time = current;

    manageApple();
    if (!m_directions.empty()) {
        m_snake.move(this->m_directions.front());
        this->m_directions.pop_front();
    } else {
        m_snake.move(NoDir);
    }

    if (hasLost()) {
        m_snake.reset(10, 5);
        this->m_directions.clear();
        m_snakeMenu.setMenuRunning(true);
        return;
    }

    m_object.objects.clear();

    m_object.objects.push_back(m_factory.createWall(0, 0, m_width, 1));
    m_object.objects.push_back(m_factory.createWall(0, 0, 1, m_height));
    m_object.objects.push_back(m_factory.createWall(0, m_height, m_width, 1));
    m_object.objects.push_back(m_factory.createWall(m_width, 0, 1, m_height + 1));
    m_object.objects.push_back(m_factory.createFood(m_apple[0], m_apple[1]));
    m_snake.toObject(m_object, m_factory);
    return;
}

arcade::data_t const &arcade::SnakeGame::getMap(void) const
{
    if (m_snakeMenu.isRunning()) {
        return m_snakeMenu.getMap();
    }
    return m_object;
}

arcade::SnakeGame::~SnakeGame()
{}
