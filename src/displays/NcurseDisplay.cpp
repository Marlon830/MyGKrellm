/*
** EPITECH PROJECT, 2023
** B-PDG-300-MPL-3-1-PDGRUSH3-marlon.pegahi
** File description:
** NcurseDisplay.cpp
*/

#include "NcurseDisplay.hpp"
#include <iostream>

std::string getHorizontalBar(std::string name, double percent, int size)
{
    int fill = percent * size / 100;
    std::string res = name + " [";
    std::ostringstream oss;
    for (int i = 0; i < fill; ++i)
    {
        res += "|";
    }
    for (int i = fill; i < 50; ++i)
    {
        res += ".";
    }
    oss << std::fixed << std::setprecision(3) << percent;
    res += "]\t" + oss.str() + "%";
    return res;
}

namespace Krell
{
    NcurseDisplay::NcurseDisplay()
    {
        _type = Krell::IDisplay::DisplayType::NCURSE;
        _lastYPos = 1;
    }

    void NcurseDisplay::open()
    {
        initscr();
        start_color();
        curs_set(0);
        nodelay(stdscr, TRUE); // getch() will be non-blocking
        keypad(stdscr, TRUE); // Enable function keys
        mousemask(ALL_MOUSE_EVENTS, NULL); // Enable mouse events
    }

    void NcurseDisplay::close()
    {
        endwin();
        _closed = true;
    }

    bool NcurseDisplay::isClosed() const
    {
        return _closed;
    }

    void NcurseDisplay::setClosed(bool closed)
    {
        _closed = closed;
    }

    void NcurseDisplay::update() {}

    std::pair<double, double> NcurseDisplay::getModuleSize(Krell::IModule &module) const
    {
        std::pair<double, double> winSize(0, 0);
        Krell::IModule::displayType type;
        size_t x_size = 0;

        for (size_t i = 0; i != module.getInfos().size(); i++)
        {
            type = std::get<2>(module.getInfos()[i]);
            if (type == Krell::IModule::HORIZONTAL_BAR)
            {
                winSize.first =  std::get<0>(module.getInfos()[i]).length() + 70;
                winSize.second += 1;
            }
            else if (type == Krell::IModule::TEXT)
            {
                x_size = std::get<0>(module.getInfos()[i]).length() + std::get<1>(module.getInfos()[i]).length() + 4;
                if (winSize.first < x_size)
                {
                    winSize.first = x_size;
                }
                winSize.second += 1;
            }
        }
        winSize.second += 2;
        if (!module.isDisplayed())
            winSize.second = 3;
        return winSize;
    }

    void NcurseDisplay::display(Krell::IModule &module, int index)
    {
        if (_ch != ERR) {
            if (_ch == 'c' && module.getName() == "CPU Infos") {
                module.switchDisplay();
            }
            if (_ch == 't' && module.getName() == "Date") {
                module.switchDisplay();
            }
            if (_ch == 'b' && module.getName() == "Battery") {
                module.switchDisplay();
            }
            if (_ch == 'n' && module.getName() == "NetworkLoad") {
                module.switchDisplay();
            }
            if (_ch == 's' && module.getName() == "System Info") {
                module.switchDisplay();
            }
            if (_ch == 'p' && module.getName() == "ProcessusInfo") {
                module.switchDisplay();
            }
            if (_ch == 'r' && module.getName() == "Ram info") {
                module.switchDisplay();
            }
            if (_ch == 'a') {
                this->close();
            }
        }
        std::pair<double, double> winSize = this->getModuleSize(module);
        Krell::IModule::displayType type;
        std::string moduleName = module.getName();
        WINDOW *win = newwin(module.isDisplayed() ? winSize.second : 1, winSize.first, index * 5, 0);    

        init_pair(1, COLOR_WHITE, COLOR_RED);
        init_pair(2, COLOR_YELLOW, COLOR_BLACK);

        wattron(win, COLOR_PAIR(1));
        box(win, 0, 0);
        mvwin(win, _lastYPos, 0);
        
        mvwprintw(win, 0, (winSize.first - moduleName.size()) / 2, "%s", moduleName.c_str());
        wattroff(win, COLOR_PAIR(1));

        if (module.isDisplayed()) {
            wattron(win, COLOR_PAIR(2));
            for (size_t i = 0; i != module.getInfos().size(); i++) {
                type = std::get<2>(module.getInfos()[i]);
                if (type == Krell::IModule::TEXT) {
                    std::string line = std::get<0>(module.getInfos()[i]) + ": " + std::get<1>(module.getInfos()[i]);
                    mvwprintw(win, i + 1, 1, "%s", line.c_str());
                } else if (type == Krell::IModule::HORIZONTAL_BAR){
                    mvwprintw(win, i + 1, 1, "%s", getHorizontalBar(std::get<0>(module.getInfos()[i]), std::stod(std::get<1>(module.getInfos()[i])), 50).c_str());
                }
            }
            wattroff(win, COLOR_PAIR(2));
        }
        wrefresh(win);
        delwin(win);
        _lastYPos += winSize.second + 1;
        mvprintw(LINES - 1, 0, "Commands: c - CPU, t - Date, b - Battery, n - Network, s - System, p - Processes, r - RAM, a - Change Lib");
        refresh();
    }

    void NcurseDisplay::event() {

        _ch = getch();
    }

    void NcurseDisplay::clear()
    {
        endwin();
        refresh();
        erase();
        _lastYPos = 0;
    }
    void NcurseDisplay::onScreen() {}
}
