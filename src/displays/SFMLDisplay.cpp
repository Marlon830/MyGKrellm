/*
** EPITECH PROJECT, 2024
** B-PDG-300-MPL-3-1-PDGRUSH3-marlon.pegahi
** File description:
** SFMLDisplay.cpp
*/

#include "SFMLDisplay.hpp"
#include <iostream>
#include <algorithm>

namespace Krell
{
    SFMLDisplay::SFMLDisplay()
    {
        _type = DisplayType::SFML;
        _window = new sf::RenderWindow(sf::VideoMode(800, 600), "Krell");
        _previousBoxPos = 0;
        _font = new sf::Font();
        _event = new sf::Event;
        _font->loadFromFile("assets/fonts/font.otf");
        _view = new sf::View(sf::FloatRect(0, 0, 800, 600));
        _window->setView(*_view);
    }

    SFMLDisplay::~SFMLDisplay()
    {
        delete _window;
        delete _font;
        delete _view;
    }

    void SFMLDisplay::clear()
    {
        _window->clear(sf::Color::Black);
    }

    void SFMLDisplay::onScreen()
    {
        _window->display();
    }

    void handleClickBox(sf::Event event, std::vector<SFMLDisplay::DisplayedModule> dpModules, sf::RenderWindow *window, sf::View *view)
    {
        for (std::size_t i = 0; i < dpModules.size(); i++)
        {
            Box *box = dpModules[i].getButton();
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Button::Left &&
                box->contains(window->mapPixelToCoords(sf::Mouse::getPosition(*window), *view)))
            {
                dpModules[i].getModule()->switchDisplay();
                return;
            }
        }
    }

    void createText(sf::Text *text, sf::Font *font, sf::Vector2f pos, std::string str, int i, sf::RenderWindow *window)
    {
        text->setOrigin(pos.x, -pos.y);
        text->setFont(*font);
        text->setString(str);
        text->setCharacterSize(12);
        text->setFillColor(sf::Color::White);
        text->setPosition(pos.x + window->getSize().x * 0.01875, 15 + (i * 30));
    }

    void SFMLDisplay::showText(sf::Vector2f pos, IModule &module, int i)
    {
        sf::Text text;
        createText(&text, _font, pos, std::get<0>(module.getInfos()[i]) + ": " + std::get<1>(module.getInfos()[i]), i, _window);
        _window->draw(text);
    }

    void SFMLDisplay::showHorizontalBar(sf::Vector2f pos, IModule &module, int i)
    {
        sf::Text text;
        createText(&text, _font, pos, std::get<0>(module.getInfos()[i]), i, _window);
        int offset = text.getCharacterSize() * text.getLetterSpacing() * text.getString().getSize();
        pos += sf::Vector2f(offset, 15 + (i * 30));
        std::string percent = std::get<1>(module.getInfos()[i]);
        Box outsideBar(sf::Vector2f(_window->getSize().x * (1 - 0.0625) - offset, 18), pos, sf::Color(220, 220, 220));
        Box insideBar(sf::Vector2f(std::max(atoi(percent.c_str()) * _window->getSize().x * (1 - 0.0625) / 100 - offset, 0.), 18), pos, sf::Color(220, 220, 220));
        insideBar.setFillColor(sf::Color(160, 0, 0));
        _window->draw(text);
        _window->draw(outsideBar);
        _window->draw(insideBar);
    }

    sf::RenderWindow *SFMLDisplay::getWindow()
    {
        return this->_window;
    }

    void SFMLDisplay::event()
    {
        delete _event;
        _event = new sf::Event;
        _window->setView(*_view);
    }

    void SFMLDisplay::display(IModule &module, int indModule)
    {

        if (indModule == 0)
            _previousBoxPos = 5;
        Box *rect;
        Box *del;
        if (module.isDisplayed())
        {
            rect = new Box(sf::Vector2f(_window->getSize().x * (1 - 0.025), 100 + 23 * module.getInfos().size()), sf::Vector2f(_window->getSize().x * 0.0125, _previousBoxPos + 10), sf::Color::White);
            rect->setFillColor(sf::Color(28, 28, 28));
            del = new Box(sf::Vector2f(20, 20), sf::Vector2f(rect->getPosition().x + 5, rect->getPosition().y + 5), sf::Color::Transparent);
            if (_dpModules.size() == static_cast<std::size_t>(indModule))
            {
                _dpModules.push_back(DisplayedModule(*rect, *del, module));
            }
            else
            {
                _dpModules[indModule].setRect(rect);
                _dpModules[indModule].setButton(del);
            }
        }
        else
        {
            rect = new Box(sf::Vector2f(_window->getSize().x * (1 - 0.025), 30), sf::Vector2f(_window->getSize().x * 0.0125, _previousBoxPos + 10), sf::Color::White);
            rect->setFillColor(sf::Color(28, 28, 28));
            del = new Box(sf::Vector2f(20, 20), sf::Vector2f(rect->getPosition().x + 5, rect->getPosition().y + 5), sf::Color::Transparent);
            if (_dpModules.size() == static_cast<std::size_t>(indModule))
            {
                _dpModules.push_back(DisplayedModule(*rect, *del, module));
            }
            else
            {
                _dpModules[indModule].setRect(rect);
                _dpModules[indModule].setButton(del);
            }
        }
        _dpModules[indModule].getButton()->setFillColor(sf::Color(160, 0, 0));
        _previousBoxPos = _dpModules[indModule].getRect()->getSize().y + _dpModules[indModule].getRect()->getPosition().y;
        sf::Vector2f pos = _dpModules[indModule].getRect()->getPosition() + sf::Vector2f(0, 25);
        sf::Event event;
        sf::Text title;
        createText(&title, _font, sf::Vector2f(0, 0), module.getName(), 0, _window);
        title.setPosition(pos + sf::Vector2f((_window->getSize().x - title.getCharacterSize() * 5) / 2, -20));
        _window->draw(*_dpModules[indModule].getRect());
        _window->draw(*_dpModules[indModule].getButton());
        while (_window->pollEvent(event))
        {
            handleClickBox(event, _dpModules, _window, _view);
            if (event.type == sf::Event::Closed)
            {
                _window->close();
            }
            if (event.type == sf::Event::Resized)
            {
                _view->setSize(event.size.width, event.size.height);
                _view->setCenter(event.size.width / 2.0f, event.size.height / 2.0f);
            }

            if (event.type == sf::Event::MouseWheelScrolled)
            {
                if (event.mouseWheelScroll.delta > 0 && _view->getCenter().y - _view->getSize().y / 2 > 0)
                {
                    _view->move(0, -20);
                }
                else if (event.mouseWheelScroll.delta < 0 && _view->getCenter().y + _view->getSize().y / 2 < _dpModules[_dpModules.size() - 1].getRect()->getPosition().y + _dpModules[_dpModules.size() - 1].getRect()->getSize().y)
                {
                    _view->move(0, 20);
                }
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::A)
                {
                    this->close();
                }
            }
        }
        if (module.isDisplayed())
        {
            for (size_t i = 0; i < module.getInfos().size(); i++)
            {
                switch (std::get<2>(module.getInfos()[i]))
                {
                case IModule::displayType::TEXT:
                    showText(pos, module, i);
                    break;

                case IModule::displayType::HORIZONTAL_BAR:
                    showHorizontalBar(pos, module, i);
                    break;
                default:
                    continue;
                }
            }
        }
        _window->draw(title);
    }

    void SFMLDisplay::update() {}
    void SFMLDisplay::open() {
        if (_window)
            delete _window;
        _window = new sf::RenderWindow(sf::VideoMode(800, 600), "Krell");

    }
    void SFMLDisplay::close() {
        _window->close();
        _closed = true;
    }

    bool SFMLDisplay::isClosed() const
    {
        return _closed;
    }

    void SFMLDisplay::setClosed(bool closed)
    {
        _closed = closed;
    }
}

Box::Box(sf::Vector2f size, sf::Vector2f pos, sf::Color outlineColor) : sf::RectangleShape(size)
{
    this->setOutlineColor(outlineColor);
    this->setOutlineThickness(2);
    this->setPosition(pos);
}

bool Box::contains(sf::Vector2f point)
{
    return (this->getPosition().x < point.x && point.x < this->getPosition().x + this->getSize().x && this->getPosition().y < point.y && point.y < this->getPosition().y + this->getSize().y);
}
