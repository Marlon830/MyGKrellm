/*
** EPITECH PROJECT, 2024
** B-PDG-300-MPL-3-1-PDGRUSH3-marlon.pegahi
** File description:
** Ram.cpp
*/

#include "Ram.hpp"
#include <iostream>
#include <sys/sysinfo.h>
#include <fstream>
#include <limits>

Ram::Ram()
{
    this->_name = "Ram info";
    this->_isDisplayed = true;
}

void Ram::update()
{
    std::string token;
    std::ifstream file("/proc/meminfo");
    int totalRam;
    int freeRam;
    int usedRam;

    this->_infos.clear();
    while (file >> token) {
        if (token == "MemTotal:") {
            unsigned long mem;
            if (file >> mem) {
                totalRam = mem;
                this->_infos.push_back(std::make_tuple("Total Ram", std::to_string((double)mem / 1000000) + " GB", Krell::IModule::displayType::TEXT));
            }
        }
        if (token == "MemAvailable:") {
            unsigned long mem;
            if (file >> mem) {
                freeRam = mem;
                this->_infos.push_back(std::make_tuple("Free Ram", std::to_string((double)mem / 1000000) + " GB", Krell::IModule::displayType::TEXT));
            }
        }
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    usedRam = totalRam - freeRam;
    this->_infos.push_back(std::make_tuple("Ram use in %", std::to_string(((double)usedRam / (double)totalRam) * 100), Krell::IModule::displayType::HORIZONTAL_BAR));
    this->_infos.push_back(std::make_tuple("Ram used", std::to_string((double)usedRam / 1000000) + "GB / " + std::to_string((double)totalRam / 1000000) + " GB", Krell::IModule::displayType::TEXT));
}
