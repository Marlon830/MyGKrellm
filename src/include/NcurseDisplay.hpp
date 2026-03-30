/*
** EPITECH PROJECT, 2023
** B-PDG-300-MPL-3-1-PDGRUSH3-marlon.pegahi
** File description:
** NcurseDisplay.hpp
*/

#ifndef NcurseDisplay_HPP_
#define NcurseDisplay_HPP_

#include "IDisplay.hpp"
#include <ncurses.h>
#include <iomanip> 

namespace Krell
{
    class NcurseDisplay : public IDisplay
    {
    public:
        // Ctor
        NcurseDisplay();

        // Member functions
        void display(IModule &module, int index);
        void update();
        void open();
        void close();
        void event();
        void clear();
        void onScreen();
        bool isClosed() const;
        void setClosed(bool closed);
        std::pair<double, double> getModuleSize(IModule &module) const;
    protected:
        std::vector<WINDOW *> _windows;
        int _lastYPos;
        int _ch = 0;
        bool _closed = false;
    };
}

#endif
