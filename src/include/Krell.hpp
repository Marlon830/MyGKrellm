/*
** EPITECH PROJECT, 2024
** B-PDG-300-MPL-3-1-PDGRUSH3-marlon.pegahi
** File description:
** Krell.hpp
*/

#ifndef Krell_HPP_
#define Krell_HPP_

#include "IDisplay.hpp"
#include "IModule.hpp"

namespace Krell
{
    class IDisplay;
    class IModule;

    class KrellCore
    {
    public:
        // Ctor
        // KrellCore();

        // Getters
        std::vector<IDisplay *> const getDisplays() const
        {
            return _displays;
        }

        std::vector<IModule *> const getModules() const
        {
            return _modules;
        }

        std::size_t getNbDisplay() const
        {
            return _displays.size();
        }

        std::size_t getNbModules() const
        {
            return _modules.size();
        }

        IDisplay::DisplayType getCurrentDisplayType() const
        {
            return _currentDisplayType;
        }

        // Setters
        void setCurrentDisplayType(IDisplay::DisplayType displayType)
        {
            this->_currentDisplayType = displayType;
        }

        // Method Functions
        void addModule(IModule &module);
        void addDisplay(IDisplay &display);
        void removeModule(int ind);
        void removeDisplay(int ind);
        void toggleModuleDisplay(IModule &module)
        {
            module.switchDisplay();
        };
        void run();
    protected:
        std::vector<IDisplay *> _displays;
        std::vector<IModule *> _modules;
        IDisplay::DisplayType _currentDisplayType = IDisplay::DisplayType::NCURSE;
    };
}

#endif
