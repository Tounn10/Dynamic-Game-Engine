/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** AEvent
*/

#include "Arcade.hpp"

#ifndef AEVENT_HPP_
    #define AEVENT_HPP_

namespace arcade {
    class AEvent : public IEvent{
        public:
            AEvent(std::string const &event);
            ~AEvent();

            std::string const &type() const override;

        protected:
            std::string m_event;
    };
}

#endif /* !AEVENT_HPP_ */
