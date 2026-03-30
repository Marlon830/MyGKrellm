/*
** EPITECH PROJECT, 2024
** B-PDG-300-MPL-3-1-PDGRUSH3-marlon.pegahi
** File description:
** Battery.hpp
*/

#ifndef Battery_HPP_
#define Battery_HPP_

#include "Krell.hpp"

class Battery : public Krell::IModule
{
public:
    // Ctor
    Battery();

    // Member functions
    void update();
};

#endif
