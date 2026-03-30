/*
** EPITECH PROJECT, 2023
** B-PDG-300-MPL-3-1-PDGRUSH3-marlon.pegahi
** File description:
** CpuInfo.hpp
*/

#ifndef CpuInfo_HPP_
#define CpuInfo_HPP_

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unistd.h>
#include "Krell.hpp"

class CpuInfo : public Krell::IModule
{
public:
    // Ctor
    CpuInfo();

    // Member functions
    void update();
private:
    std::vector<unsigned long long> readCPUStats();
    std::vector<unsigned long long> _lastCpuStat;
};

#endif