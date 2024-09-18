/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** CoreLibManger
*/

#include <iostream>
#include "Arcade.hpp"
#include "DirectoryLister/SafeDirectoryLister.hpp"

#ifndef CORELIBMANGER_HPP_
    #define CORELIBMANGER_HPP_

class CoreLibManager {
    public:
        CoreLibManager(std::string const &folder, std::string const &subfolder,
            std::string const &current, std::vector<std::string> const &vectorLib);
        ~CoreLibManager();

        void update(void);
        void addData(std::vector<std::unique_ptr<arcade::IObject>> &vectorToFill, size_t x, size_t y, size_t nb, bool isFocused);
        std::string select(void);
        void moveFocus(std::string const &events);

    protected:
        std::vector<std::string> const &m_possibleLibs;
        std::string m_folder;
        std::string m_subfolder;
        std::string m_nameOfSelected;

        size_t m_focused;
        size_t m_selected;
        bool m_hasASelected;

        std::vector<std::string> m_libs;
        SafeDirectoryLister m_dirLister;
};

#endif /* !CORELIBMANGER_HPP_ */
