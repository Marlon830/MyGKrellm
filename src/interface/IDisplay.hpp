/*
** EPITECH PROJECT, 2024
** B-PDG-300-MPL-3-1-PDGRUSH3-marlon.pegahi
** File description:
** IDisplay.hpp
*/

#ifndef IDisplay_HPP_
#define IDisplay_HPP_

#include "IModule.hpp"
namespace Krell
{
    class IDisplay
    {
    public:
        enum DisplayType
        {
            NCURSE,
            SFML
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
        virtual ~IDisplay(){};

        // Member functions
        DisplayType getType() const
        {
            return _type;
        }
        virtual void display(IModule &module, int moduleInd) = 0;
        virtual void update() = 0;
        virtual void open() = 0;
        virtual void close() = 0;
        virtual void event() = 0;
        virtual void clear() = 0;
        virtual void onScreen() = 0;
        virtual bool isClosed() const = 0;
        virtual void setClosed(bool closed) = 0;
    protected:
        // Properties
        DisplayType _type;
        bool _closed = false;
    };
}

#endif
