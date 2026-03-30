/*
** EPITECH PROJECT, 2024
** B-PDG-300-MPL-3-1-PDGRUSH3-marlon.pegahi
** File description:
** DateTime.cpp
*/

#include "NetworkLoad.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

NetworkLoad::NetworkLoad()
{
    this->_name = "NetworkLoad";
    this->_isDisplayed = false;
}

void NetworkLoad::update()
{
    this->_infos.clear();
    std::ifstream file("/proc/net/dev");
    std::string line;

    while (std::getline(file, line)) {
        if (line.find(':') != std::string::npos) {
            long long int bytesReceive;
            long long int bytesSent;
            std::string interface = line.substr(0, line.find(':'));
            line = line.substr(line.find(':') + 1);
            std::istringstream iss(line);

            iss >> bytesReceive >> bytesSent;
            this->_infos.push_back(std::make_tuple("Interface", interface, Krell::IModule::displayType::TEXT));
            this->_infos.push_back(std::make_tuple("Bytes received", std::to_string(bytesReceive), Krell::IModule::displayType::TEXT));
            this->_infos.push_back(std::make_tuple("Bytes sent", std::to_string(bytesSent), Krell::IModule::displayType::TEXT));
        }
    }
}
