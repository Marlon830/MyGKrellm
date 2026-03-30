/*
** EPITECH PROJECT, 2023
** B-PDG-300-MPL-3-1-PDGRUSH3-marlon.pegahi
** File description:
** CpuInfo.cpp
*/

#include "CpuInfo.hpp"
#include <iostream>
#include <stdlib.h>

CpuInfo::CpuInfo()
{
    this->_name = "CPU Infos";
    this->_isDisplayed = true;
}

std::vector<unsigned long long> CpuInfo::readCPUStats()
{
    std::vector<unsigned long long> cpuStats;
    std::ifstream statFile("/proc/stat");
    std::string line;

    if (!statFile.is_open())
    {
        return cpuStats;
    }

    while (std::getline(statFile, line))
    {
        std::istringstream iss(line);
        std::string cpuLabel;
        iss >> cpuLabel;

        if (cpuLabel.find("cpu") == std::string::npos)
        {
            break;
        }

        unsigned long long value;
        while (iss >> value)
        {
            cpuStats.push_back(value);
        }
    }

    return cpuStats;
}

void CpuInfo::update()
{
    this->_infos.clear();
    std::vector<unsigned long long> stats = readCPUStats();
    if (!_lastCpuStat.empty())
    {
        for (size_t i = 0; i + 19 < _lastCpuStat.size(); i += 10)
        {
            unsigned long long startIdle = _lastCpuStat[i + 3];
            unsigned long long endIdle = stats[i + 3];
            unsigned long long startTotal = 0;
            unsigned long long endTotal = 0;

            for (size_t j = i; j < i + 10; ++j)
            {
                startTotal += _lastCpuStat[j];
                endTotal += stats[j];
            }

            unsigned long long totalDiff = endTotal - startTotal;
            unsigned long long idleDiff = endIdle - startIdle;
            double percent = 100.0 * (1.0 - static_cast<double>(idleDiff) / totalDiff);

            this->_infos.push_back(std::make_tuple("Core " + std::to_string(i / 10), std::to_string(percent), Krell::IModule::displayType::HORIZONTAL_BAR));
        }
        _lastCpuStat.clear();
    } else {
        for (size_t i = 0; i + 19 < stats.size(); i += 10)
        {
            this->_infos.push_back(std::make_tuple("Core " + std::to_string(i / 10), std::to_string(0.0), Krell::IModule::displayType::HORIZONTAL_BAR));
        }
    }
    _lastCpuStat = stats;
}
