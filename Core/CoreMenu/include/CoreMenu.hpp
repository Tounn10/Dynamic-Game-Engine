/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** CoreMenu
*/

#include "Arcade.hpp"
#include "CoreLibManager.hpp"

#include <map>
#include <functional>

#ifndef COREMENU_HPP_
    #define COREMENU_HPP_

namespace arcade {
    enum Focus {
        Games,
        Graphics,
        Name,
        NB_Focus
    };

    class CoreMenu : public IGameModule {
        public:
            CoreMenu(void);
            ~CoreMenu();

            void manageEvent(std::vector<std::unique_ptr<IEvent>> const &) override;
            void iterate(void) override;
            data_t const &getMap(void) const override;

            void addToDisplayName(std::string const &, int x, int y);

            void updateLibsAvailable(void);
            void moveFocusRight(void);
            void moveFocusLeft(void);
            void moveFocusUp(void);
            void moveFocusDown(void);
            void select(void);
            void switchRunTime(void);

        protected:
            data_t m_data;
            std::string m_folder;

            Focus m_focus;
            std::vector<std::string> m_graphicsPossible;
            std::vector<std::string> m_gamesPossible;

            CoreLibManager m_gamesManager;
            CoreLibManager m_graphicsManager;

            std::string name;
            std::string score;

            std::string m_userName;
            std::map<std::string, std::function<void (CoreMenu &)>> m_mapOfEvent;
    };
}

#endif /* !COREMENU_HPP_ */
