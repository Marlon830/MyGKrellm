/*
** EPITECH PROJECT, 2024
** B-PDG-300-MPL-3-1-PDGRUSH3-marlon.pegahi
** File description:
** DateTime.cpp
*/

#include "DateTime.hpp"
#include <iostream>
#include <ctime>
#include <iomanip>

DateTime::DateTime()
{
    this->_name = "Date";
    this->_isDisplayed = true;
}

std::string reformatDate(const std::string& date) {
    std::tm tm = {};
    std::stringstream ss(date);
    ss >> std::get_time(&tm, "%a %b %d %H:%M:%S %Y");
    if (ss.fail()) {
        // Handle error
        return "";
    }

    std::stringstream result;
    result << std::put_time(&tm, "%d/%m/%Y %H:%M:%S");
    return result.str();
}

void DateTime::update()
{
    this->_infos.clear();
    time_t now = time(0);
    char* dt = ctime(&now);

    this->_infos.push_back(std::make_tuple("Date Time", reformatDate(dt), Krell::IModule::displayType::TEXT));
}
