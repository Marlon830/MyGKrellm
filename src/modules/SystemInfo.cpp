/*
** EPITECH PROJECT, 2024
** B-PDG-300-MPL-3-1-PDGRUSH3-marlon.pegahi
** File description:
** SystemInfo.cpp
*/

#include "SystemInfo.hpp"
#include <sys/utsname.h>
#include <unistd.h>

SystemInfo::SystemInfo()
{
    this->_name = "System Info";
    this->_isDisplayed = true;
}

void SystemInfo::update()
{
    this->_infos.clear();
    struct utsname unameData;

    uname(&unameData);
    this->_infos.push_back(std::make_tuple("System Name", unameData.sysname, Krell::IModule::displayType::TEXT));
    this->_infos.push_back(std::make_tuple("Host Name", unameData.nodename, Krell::IModule::displayType::TEXT));
    this->_infos.push_back(std::make_tuple("Kernel version", unameData.release, Krell::IModule::displayType::TEXT));
    this->_infos.push_back(std::make_tuple("Operating system", unameData.version, Krell::IModule::displayType::TEXT));
    this->_infos.push_back(std::make_tuple("Machine", unameData.machine, Krell::IModule::displayType::TEXT));
    this->_infos.push_back(std::make_tuple("User Name", getlogin(), Krell::IModule::displayType::TEXT));
}
