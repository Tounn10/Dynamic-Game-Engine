/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** AEvent
*/

#include "AEvent.hpp"

arcade::AEvent::AEvent(std::string const &event) :
m_event(event)
{}

std::string const &arcade::AEvent::type(void) const
{
    return m_event;
}

arcade::AEvent::~AEvent()
{}
