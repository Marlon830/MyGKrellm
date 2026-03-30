/*
** EPITECH PROJECT, 2024
** B-PDG-300-MPL-3-1-PDGRUSH3-marlon.pegahi
** File description:
** Krell.cpp
*/

#include "Krell.hpp"
#include <iostream>
#include <unistd.h>
#include <ctime>

namespace Krell
{

    void KrellCore::addDisplay(IDisplay &display)
    {
        _displays.insert(_displays.end(), &display);
    }

    void KrellCore::addModule(IModule &module)
    {
        _modules.insert(_modules.end(), &module);
    }

    void KrellCore::run()
    {
        clock_t time_req;
        time_req = clock();
        double now = 0;

        if (_currentDisplayType > _displays.size())
            throw IDisplay::Error("Display type not found");
        _displays[_currentDisplayType]->open();
        if (_currentDisplayType == IDisplay::DisplayType::SFML) {
            for (size_t i = 0; i < _modules.size(); i++)
                _modules[i]->update();
        }
        _displays[0]->setClosed(false);
        _displays[1]->setClosed(false);
        while (true) {
            _displays[_currentDisplayType]->clear();
            _displays[_currentDisplayType]->event();
            if (_modules.size() == 0) {
                _displays[_currentDisplayType]->close();
                return;
            }
            if (now >= 500000) {
                time_req = clock();
            }
            now = clock() - time_req;
            for (size_t i = 0; i < _modules.size(); i++) {
                if (_currentDisplayType == IDisplay::DisplayType::SFML) {
                    if (now >= 500000) {
                        _modules[i]->update();
                    }
                } else {
                    _modules[i]->update();
                }
                _displays[_currentDisplayType]->display(*_modules[i], i);
                if (_displays[_currentDisplayType]->isClosed()) {
                    _currentDisplayType = static_cast<IDisplay::DisplayType>(!_currentDisplayType);
                    return run();
                }
            }
            _displays[_currentDisplayType]->onScreen();
            if (_currentDisplayType == IDisplay::DisplayType::NCURSE)
                sleep(1);
        }
    }
}
