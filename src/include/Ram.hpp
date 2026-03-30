/*
** EPITECH PROJECT, 2024
** B-PDG-300-MPL-3-1-PDGRUSH3-marlon.pegahi
** File description:
** Ram.hpp
*/

#ifndef Ram_HPP_
#define Ram_HPP_

#include "Krell.hpp"

class Ram : public Krell::IModule
{
public:
    // Ctor
    Ram();

    // Member functions
    void update();
};

#endif
