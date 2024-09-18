/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** CoreLibManager
*/

#include "AObject.hpp"
#include "CoreLibManager.hpp"
#include <regex>
#include <algorithm>


CoreLibManager::CoreLibManager(std::string const &folder, std::string const &subfolder,
            std::string const &current, std::vector<std::string> const &vectorLib) :
m_possibleLibs(vectorLib), m_folder(folder), m_subfolder(subfolder), m_nameOfSelected(current), m_focused(0), m_selected(0)
{
    m_hasASelected = true;
}

void CoreLibManager::addData(std::vector<std::unique_ptr<arcade::IObject>> &vectorToFill, size_t x, size_t y, size_t nb, bool isFocused)
{
    unsigned char lux = (isFocused) ? 255 : 150;
    std::array<unsigned char, 3> color;

    if (m_libs.size() == 0) {
        return;
    }
    vectorToFill.push_back(std::make_unique<arcade::AObject>(lux, lux, lux, x, y + m_focused, 20, 1, "", ' ', arcade::Graphic));
    for (std::size_t i = 0; i < nb && i  < m_libs.size(); ++i) {
        if (i == m_focused) {
            color = {0, 0, 0};
        } else {
            color = {lux, lux, lux};
        }
        if (i == m_selected && m_hasASelected) {
            color = {0, 0, 255};
        }
        std::string tmp = m_libs[i];
        size_t pos = tmp.find_last_of("/");
        if (pos != std::string::npos) {
            tmp = tmp.substr(pos + 1);
        }
        vectorToFill.push_back(std::make_unique<arcade::AObject>(color[0], color[1], color[2], x, y + i, 1, 1, tmp, ' ', arcade::Text));
    }
}

CoreLibManager::~CoreLibManager()
{}

std::string CoreLibManager::select(void)
{
    if (m_libs.size() == 0) {
        return "";
    }
    m_selected = m_focused;
    m_hasASelected = true;
    m_nameOfSelected = m_libs[m_selected];
    return m_nameOfSelected;
}

void CoreLibManager::moveFocus(std::string const &event)
{
    if (m_libs.size() == 0) {
        return;
    }
    if (event =="Up") {
        if (m_focused > 0) {
            m_focused -= 1;
        } else {
            m_focused = m_libs.size() - 1;
        }
    }
    if (event =="Down" ) {
        if (m_libs.size() != 0 && m_focused < (m_libs.size() - 1)) {
            m_focused += 1;
        } else {
            m_focused = 0;
        }
    }
    
}

void CoreLibManager::update(void)
{
    std::string nameFile;
    m_libs.clear();

    m_dirLister.open(m_folder, false);
    while (m_dirLister.isGood()) {
        nameFile = m_dirLister.get();
        if (std::find(m_possibleLibs.begin(), m_possibleLibs.end(), nameFile) != m_possibleLibs.end()) {
            m_libs.push_back(m_folder + "/" + nameFile);
        }
    }
    try {
        m_dirLister.open(m_folder + "/" + m_subfolder, false);
        while (m_dirLister.isGood()) {
            nameFile = m_dirLister.get();
            std::regex soFileRegex(".+\\.so$");
            if (std::regex_match(nameFile, soFileRegex)) {
                m_libs.push_back(m_folder + "/" + m_subfolder + "/" + nameFile);
            }
        }
    } catch (IDirectoryLister::OpenFailureException &e) {
        return;
    }
    auto finder = std::find(m_libs.begin(), m_libs.end(), m_nameOfSelected);
    if (finder != m_libs.end()) {
        m_hasASelected = true;
        m_selected = std::distance(m_libs.begin(), finder);
    } else {
        m_hasASelected = false;
    }
    if (m_focused >= m_libs.size()) {
        m_focused = 0;
    }
}
