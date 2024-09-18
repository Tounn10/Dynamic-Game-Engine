/*
** EPITECH PROJECT, 2024
** Game
** File description:
** Ray
*/

#include <array>

#ifndef RAY_HPP_
    #define RAY_HPP_

class Ray {
    public:
        Ray(std::array<double, 3>, double, double);
        ~Ray();

        std::array<double, 3> const& getStart() const;
        std::array<double, 3> getDirection() const;

        void setStart(std::array<double, 3> const &);
        void setDirection(std::array<double, 3> const &);

        void turnHorizontally(double);
        void turnVertically(double);
        void move(double);

        bool operator==(Ray const &other) const;

    protected:
        std::array<double, 3> m_start;
        double m_horizontalAngle;
        double m_verticalAngle;
};

#endif /* !RAY_HPP_ */
