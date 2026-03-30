/*
** EPITECH PROJECT, 2024
** B-PDG-300-MPL-3-1-PDGRUSH3-marlon.pegahi
** File description:
** DateTime.cpp
*/

#include "Battery.hpp"
#include <fstream>

Battery::Battery()
{
    this->_name = "Battery";
    this->_isDisplayed = true;
}

void Battery::update()
{
    this->_infos.clear();
    std::string line;
    std::ifstream file("/sys/class/power_supply/BAT0/capacity");

    if (file.is_open()) {
        while (getline(file, line)) {
            this->_infos.push_back(std::make_tuple("Battery", line, Krell::IModule::displayType::HORIZONTAL_BAR));
        }
        file.close();
    }
}
