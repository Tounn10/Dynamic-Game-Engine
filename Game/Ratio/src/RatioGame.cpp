/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** Snake
*/

#include "RatioGame.hpp"
#include "AObject.hpp"
#include "Ray.hpp"
#include "Cube.hpp"
#include <memory>
#include <cmath>
#include <cfloat>

extern "C" std::unique_ptr<arcade::IGameModule> entryPoint()
{
    return std::make_unique<arcade::RatioGame>();
}

double arcade::RatioGame::computeDistance(std::array<double, 3> const &pos1, std::array<double, 3> const &pos2) const
{
    return std::sqrt((pos1[0] - pos2[0]) * (pos1[0] - pos2[0]) +
                    (pos1[1] - pos2[1]) * (pos1[1] - pos2[1]) +
                    (pos1[2] - pos2[2]) * (pos1[2] - pos2[2]));
}

arcade::RatioGame::RatioGame() :
m_nb_walls(0), m_height(40), m_width(64),
m_last_time(std::chrono::high_resolution_clock::now()),
m_ray({-10, 10, 5}, 0, 0)
{
    // P
    m_object.size = {m_width, m_height};
    m_object.objects.clear();
    m_cubes.push_back(Cube({1.0, 1.0, 1.0}, {1.0, 1.0, 10.0}));
    m_cubes.push_back(Cube({1.0, 2.0, 1.0}, {1.0, 3.0, 1.0}));
    m_cubes.push_back(Cube({1.0, 5.0, 2.0}, {1.0, 1.0, 2.0}));
    m_cubes.push_back(Cube({1.0, 3.0, 4.0}, {1.0, 2.0, 1.0}));

    // end of the R
    m_cubes.push_back(Cube({1.0, 2.0, 5.0}, {1.0, 1.0, 1.0}));
    m_cubes.push_back(Cube({1.0, 3.0, 6.0}, {1.0, 1.0, 1.0}));
    m_cubes.push_back(Cube({1.0, 4.0, 7.0}, {1.0, 1.0, 1.0}));
    m_cubes.push_back(Cube({1.0, 5.0, 8.0}, {1.0, 1.0, 3.0}));

    // .
    m_cubes.push_back(Cube({1.0, 7.0, 10.0}, {1.0, 1.0, 1.0}));
    // S
    m_cubes.push_back(Cube({1.0, 9.0, 10.0}, {1.0, 2.0, 1.0}));
    m_cubes.push_back(Cube({1.0, 11.0, 8.0}, {1.0, 1.0, 2.0}));
    m_cubes.push_back(Cube({1.0, 9.0, 7.0}, {1.0, 2.0, 1.0}));
    m_cubes.push_back(Cube({1.0, 8.0, 5.0}, {1.0, 1.0, 2.0}));
    m_cubes.push_back(Cube({1.0, 9.0, 4.0}, {1.0, 3.0, 1.0}));

    // O
    m_cubes.push_back(Cube({1.0, 14.0, 10.0}, {1.0, 3.0, 1.0}));
    m_cubes.push_back(Cube({1.0, 13.0, 7.0}, {1.0, 1.0, 3.0}));
    m_cubes.push_back(Cube({1.0, 17.0, 7.0}, {1.0, 1.0, 3.0}));
    m_cubes.push_back(Cube({1.0, 14.0, 6.0}, {1.0, 3.0, 1.0}));
}

void arcade::RatioGame::manageEvent(std::vector<std::unique_ptr<arcade::IEvent>> const &events)
{
    if (events.size() == 0) {
        return;
    }
    if (events[0]->type() == "F") {
        m_ray.turnVertically(0.1);
    }
    if (events[0]->type() == "R") {
        m_ray.turnVertically(-0.1);
    }
    if (events[0]->type() == "E") {
        m_ray.turnHorizontally(0.1);
    }
    if (events[0]->type() == "A") {
        m_ray.turnHorizontally(-0.1);
    }
    if (events[0]->type() == "Z") {
        m_ray.move(1);
    }
    if (events[0]->type() == "S") {
        m_ray.move(-1);
    }
    if (events[0]->type() == "Q") {
        m_ray.turnHorizontally(-M_PI / 2);
        m_ray.move(1);
        m_ray.turnHorizontally(M_PI / 2);
    }
    if (events[0]->type() == "D") {
        m_ray.turnHorizontally(M_PI / 2);
        m_ray.move(1);
        m_ray.turnHorizontally(-M_PI / 2);
    }
    if (events[0]->type() == "G") {
        std::array<double, 3> tmp = m_ray.getStart();
        m_ray.setStart({tmp[0], tmp[1], tmp[2] + 0.2});
    }
    if (events[0]->type() == "T") {
        std::array<double, 3> tmp = m_ray.getStart();
        m_ray.setStart({tmp[0], tmp[1], tmp[2] - 0.2});
    }
    return;
}

double arcade::RatioGame::computeSingleRay(Ray const &ray) const
{
    double closestDistance = DBL_MAX;
    std::array<double, 3> tmp;

    for (const auto& cube : m_cubes) {
        if (cube.fillCollisionPoint(ray, tmp)) {
            double distance = computeDistance(ray.getStart(), tmp);
            if (distance < closestDistance) {
                closestDistance = distance;
            }
        }
    }
    return closestDistance;
}

void arcade::RatioGame::iterate(void)
{
    m_object.objects.clear();
    Ray tmp(m_ray);

    for (int i = -(m_width / 2); i < (m_width / 2); i++) {
        for (int j = -(m_height / 2); j < (m_height / 2); j++) {
            tmp = m_ray;
            tmp.turnVertically(0.01 * j);
            tmp.turnHorizontally(0.01 * i);
            double distance = computeSingleRay(tmp);
            if (distance == DBL_MAX || distance < 0) {
                continue;
            }
            distance *= 4;
            if (distance > 255) {
                m_object.objects.push_back(std::make_unique<arcade::AObject>(0, 0, 0, i + 20, j + 20, 1, 1, "", ' ', Graphic));
                continue;
            }
            m_object.objects.push_back(std::make_unique<arcade::AObject>(255 - distance, 255 - distance, 255 - distance, i + 20, j + 20, 1, 1, "", ' ', Graphic));
        }
    }
}


arcade::data_t const &arcade::RatioGame::getMap(void) const
{
    return m_object;
}

arcade::RatioGame::~RatioGame()
{}
