/*
** EPITECH PROJECT, 2024
** B-PDG-300-MPL-3-1-PDGRUSH3-marlon.pegahi
** File description:
** SFMLDisplay.hpp
*/

#ifndef SFMLDisplay_HPP_
#define SFMLDisplay_HPP_

#include "IDisplay.hpp"
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Box : public sf::RectangleShape {
    public:
        Box(sf::Vector2f size, sf::Vector2f pos, sf::Color outlineColor);
        bool contains(sf::Vector2f point);
};

namespace Krell
{
    class SFMLDisplay : public IDisplay
    {
    public:
        // Ctor
        SFMLDisplay();

        // Member functions
        void display(IModule &module, int indModule);
        ~SFMLDisplay();
        void update() override;
        void open() override;
        void close() override;
        void event() override;
        void clear() override;
        void onScreen() override;
        bool isClosed() const override;
        void setClosed(bool closed) override;
        sf::RenderWindow *getWindow();
        void showText(sf::Vector2f pos, IModule &module, int i);
        void showHorizontalBar(sf::Vector2f pos, IModule &module, int i);
        class DisplayedModule {
            public:
                DisplayedModule(Box &rect, Box &button, IModule& module) : _module(&module), _rect(&rect), _button(&button) {
                }

                void setRect(Box *rect) {
                    _rect = rect;
                }

                void setButton(Box *button) {
                    _button = button;
                }
                Box *getRect() {
                    return _rect;
                }
                Box *getButton() {
                    return _button;
                }
                IModule *getModule() {
                    return _module;
                }
            protected:
                IModule *_module;
                Box *_rect;
                Box *_button;
                
        };
    protected:
        sf::RenderWindow *_window;
        int _previousBoxPos;
        sf::Font *_font;
        sf::Event *_event;
        std::vector<DisplayedModule> _dpModules;
        sf::View *_view;
        bool _closed = false;
    };
}

#endif
