/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** Snake
*/

#include "Snake.hpp"
#include "AObject.hpp"

arcade::Snake::Snake(int x, int y)
{
    reset(x, y);
}

bool arcade::Snake::isAPartOf(std::array<int, 2> const &elem) const
{
    auto it = m_snake.begin();
    for (; it != m_snake.end(); ++it) {
        if ((*it)[0] == elem[0] && (*it)[1] == elem[1]) {
            return true;
        }
    }
    return false;
}

void arcade::Snake::reset(int x, int y)
{
    m_snake.clear();
    m_snake.push_back({x, y});
    m_snake.push_back({x, y});
    m_snake.push_back({x, y});
    m_snake.push_back({x, y});
    m_direction = NoDir;
    hasGrown = false;
}

std::list<std::array<int, 2>> const &arcade::Snake::getTail(void) const
{
    return m_snake;
}

void arcade::Snake::move(SnakeDirection dir)
{
    int x = m_snake.front()[0];
    int y = m_snake.front()[1];

    if ((m_direction == Right && dir == Left)
        || (m_direction == Left && dir == Right)
        || (m_direction == Up && dir == Down)
        || (m_direction == Down && dir == Up)) {
            dir = m_direction;
    }
    if (dir != NoDir)
        m_direction = dir;
    if (m_direction == Up) {
        y -= 1;
    }
    if (m_direction == Down) {
        y += 1;
    }
    if (m_direction == Left) {
        x -= 1;
    }
    if (m_direction == Right) {
        x += 1;
    }
    m_snake.push_front({x, y});
    if (!hasGrown) {
        m_snake.pop_back();
    } else {
        hasGrown = !hasGrown;
    }
}

bool arcade::Snake::isTouchingItsOwnTail(void) const
{
    int x = m_snake.front()[0];
    int y = m_snake.front()[1];
    auto it = m_snake.begin();

    if (m_direction == NoDir) {
        return false;
    }
    ++it;
    for (; it != m_snake.end(); ++it) {
        if ((*it)[0] == x && (*it)[1] == y) {
            return true;
        }
    }
    return false;
}

void arcade::Snake::addElem(void)
{
    hasGrown = true;
}

char arcade::Snake::getAscii(std::list<std::array<int, 2>>::const_iterator const &it) const
{
    if (it == m_snake.begin()) {
        return 'O';
    }
    else if (it == std::prev(m_snake.end())) {
        return 'X';
    }
    if ((*std::prev(it))[0] == (*std::next(it))[0]) {
        return '|';
    }
    if ((*std::prev(it))[1] == (*std::next(it))[1]) {
        return '-';
    }
    return '+';
}

arcade::SnakeDirection arcade::Snake::getDirectionPart(std::list<std::array<int, 2>>::const_iterator const &it) const
{
    auto prev = std::prev(it);
    if ((*prev)[0] == (*it)[0]) {
        if ((*prev)[1] > (*it)[1])
            return Up;
        return Down;
    }
    if ((*prev)[0] > (*it)[0])
        return Left;
    return Right;
}

std::string arcade::Snake::dirToString(SnakeDirection dir) const
{
    switch (dir) {
        case Right:
            return "right";
        case Left:
            return "left";
        case Up:
            return "up";
        case Down:
            return "down";
        default:
            return "";
    }
}

std::string arcade::Snake::getAsset(std::list<std::array<int, 2>>::const_iterator const &it) const
{
    if (it == m_snake.begin())
        return "./assets/snake/head_" + dirToString(m_direction) + ".png";

    if (it == std::prev(m_snake.end()))
        return "./assets/snake/tail_" + dirToString(getDirectionPart(it)) + ".png";

    auto prev = std::prev(it);
    auto next = std::next(it);
    if ((*prev)[1] == (*next)[1]) {
        return "./assets/snake/body_horizontal.png";
    } else if ((*prev)[0] == (*next)[0]) {
        return "./assets/snake/body_vertical.png";
    }
    SnakeDirection dir1 = (arcade::SnakeDirection)(((int)getDirectionPart(it) + 2) % (int)NoDir);
    SnakeDirection dir2 = getDirectionPart(next);
    SnakeDirection UpDown = (dir1 == Up || dir1 == Down) ? dir1 : dir2;
    SnakeDirection LeftRight = (dir1 == Left || dir1 == Right) ? dir1 : dir2;
    return "./assets/snake/body_" + dirToString(UpDown) + dirToString(LeftRight) + ".png";
}

void arcade::Snake::toObject(arcade::data_t &data, SnakeFactory const &factory) const
{
    char c = '+';
    auto it = m_snake.begin();
    c = getAscii(it);
    std::string asset = getAsset(it);
    data.objects.push_back(factory.createSnakeHead(asset, (*it)[0], (*it)[1]));
    it++;
 
    for (; it != m_snake.end(); ++it) {
        c = getAscii(it);
        asset = getAsset(it); 
        data.objects.push_back(factory.createSnakeParts(asset, c, (*it)[0], (*it)[1]));
    }
}
