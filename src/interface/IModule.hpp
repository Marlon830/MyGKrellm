/*
 ** EPITECH PROJECT, 2024
 ** B-PDG-300-MPL-3-1-PDGRUSH3-marlon.pegahi
 ** File description:
 ** IModule.hpp
 */

#ifndef IModule_HPP_
#define IModule_HPP_

#include <string>
#include <vector>
#include <tuple>

namespace Krell
{
    class IModule
    {
    public:
        enum displayType
        {
            HORIZONTAL_BAR,
            VERTICAL_BAR,
            TEXT
        };

        class Error : std::exception
        {
        public:
            Error(std::string message) : _message(message){};
            const char *what() const noexcept { return _message.c_str(); }

        protected:
            std::string _message;
        };

        // Dtor
        virtual ~IModule(){};

        // Member functions
        virtual void update() = 0;

        // Getter
        std::string const getName() const
        {
            return _name;
        }

        bool isDisplayed() const
        {
            return _isDisplayed;
        }

        void switchDisplay()
        {
            _isDisplayed = !_isDisplayed;
        }

        std::vector<std::tuple<std::string, std::string, displayType>> const getInfos() const
        {
            return _infos;
        }

    protected:
        std::string _name;
        bool _isDisplayed;
        std::vector<std::tuple<std::string, std::string, displayType>> _infos;
    };
}

#endif
