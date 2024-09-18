/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** Core
*/

#include "Loader/DLLoader.hpp"
#include "Arcade.hpp"

#include <map>
#include <functional>

#ifndef CORE_HPP_
    #define CORE_HPP_

namespace arcade {

    class Core {
        public:
            Core(std::string const &graphicLib);
            ~Core();
            void loop(void);
            void manageEvent(std::vector<std::unique_ptr<IEvent>> const &events);
            void checkQuit(std::vector<std::unique_ptr<IEvent>> const &events);

            void openGameInPause(std::string const &libName);
            void openNewGraphics(std::string const &libName);

            bool pause(void);
            bool play(void);
            bool switchGraphicRunTime(void);
            bool enterEvent(void);

            int getExitValue(void) const;

        protected:
            std::unique_ptr<arcade::IDisplayModule> m_graphicsModule;
            std::unique_ptr<arcade::IGameModule> m_gameModule;
            DLLdr::DLLoader<arcade::IDisplayModule> m_graphicsLoader;
            DLLdr::DLLoader<arcade::IGameModule> m_gameLoader;

            DLLdr::DLLoader<arcade::IGameModule> m_coreMenuLoader;

            std::unique_ptr<arcade::IGameModule> m_gamePaused;

            std::string m_runningGame;
            std::string m_runningGraphic;

            std::map<std::string, std::function<bool (Core &)>> m_mapOfEventPause;
            std::map<std::string, std::function<bool (Core &)>> m_mapOfEventPlay;

            bool m_run;
            bool m_isPaused;

            std::string m_userName;

            int m_exitValue;
    };
}

#endif /* !CORE_HPP_ */
