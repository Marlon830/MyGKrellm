/*
** EPITECH PROJECT, 2024
** B-PDG-300-MPL-3-1-PDGRUSH3-marlon.pegahi
** File description:
** DateTime.hpp
*/

#ifndef DateTime_HPP_
#define DateTime_HPP_

#include "Krell.hpp"

class DateTime : public Krell::IModule
{
public:
    // Ctor
    DateTime();

    // Member functions
    void update();
};

#endif
