/*
** EPITECH PROJECT, 2024
** B-PDG-300-MPL-3-1-PDGRUSH3-marlon.pegahi
** File description:
** SystemInfo.hpp
*/

#ifndef SystemInfo_HPP_
#define SystemInfo_HPP_

#include "Krell.hpp"

class SystemInfo : public Krell::IModule
{
public:
    // Ctor
    SystemInfo();

    // Member functions
    void update();
};

#endif
