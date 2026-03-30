/*
** EPITECH PROJECT, 2024
** B-PDG-300-MPL-3-1-PDGRUSH3-marlon.pegahi
** File description:
** Battery.hpp
*/

#ifndef ProcessusInfo_HPP_
#define ProcessusInfo_HPP_

#include "Krell.hpp"

class ProcessusInfo : public Krell::IModule
{
public:
    // Ctor
    ProcessusInfo();

    // Member functions
    void update();
};

#endif
