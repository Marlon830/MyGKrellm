/*
** EPITECH PROJECT, 2024
** B-PDG-300-MPL-3-1-PDGRUSH3-marlon.pegahi
** File description:
** DateTime.cpp
*/

#include "ProcessusInfo.hpp"
#include <dirent.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <cmath>

ProcessusInfo::ProcessusInfo()
{
    this->_name = "ProcessusInfo";
    this->_isDisplayed = false;
}

double GetCPUUsage(int pid) {
    std::ifstream stat("/proc/" + std::to_string(pid) + "/stat");
    std::string stats;
    std::getline(stat, stats);
    std::istringstream iss(stats);
    std::string temp;
    for (int i = 0; i < 13; i++) {
        iss >> temp;
    }
    long utime, stime, cutime, cstime;
    iss >> utime >> stime >> cutime >> cstime;
    long total_time = utime + stime + cutime + cstime;
    long clock_ticks = sysconf(_SC_CLK_TCK);
    std::ifstream uptime_file("/proc/uptime");
    double uptime, idle_time;
    uptime_file >> uptime >> idle_time;
    double total_time_secs = total_time / double(clock_ticks);
    double idle_time_secs = idle_time / clock_ticks;
    double total_cpu_time = uptime - idle_time_secs;
    return (total_time_secs / total_cpu_time) * 100.0;
}

bool isNumber(std::string str) {
    for (char c : str) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

double roundMem(double x) {
    return std::round(x * 100.0) / 100.0;
}

void ProcessusInfo::update() {
    this->_infos.clear();
    DIR* dir = opendir("/proc");
    std::string temp = "";
    struct dirent* entry;
    int count = 0;

    if (dir != nullptr) {
        while ((entry = readdir(dir)) != nullptr && count < 25) {
            if (entry->d_type == DT_DIR && isNumber(entry->d_name)) {
                temp.append(entry->d_name);
                std::ifstream stat("/proc/" + temp + "/stat");
                temp.clear();
                std::string stats;
                std::getline(stat, stats);
                std::istringstream iss(stats);
                std::string name;
                iss >> name;
                iss >> name;
                name = name.substr(1, name.length() - 2);
                std::string ignore;
                for (int i = 0; i < 8; i++) {
                    iss >> ignore;
                }
                long mem;
                iss >> mem;
                mem = mem / 1024;
                double cpuUsage = GetCPUUsage(atoi(entry->d_name));
                std::string cpuUsageStr = std::to_string(roundMem(cpuUsage));
                cpuUsageStr = cpuUsageStr.substr(0, cpuUsageStr.find(".") + 3);
                this->_infos.push_back(std::make_tuple("Processus", "Process Name: " + name + " Memory Usage: " + std::to_string(mem) + " KB CPU Usage: " + cpuUsageStr + "%", Krell::IModule::displayType::TEXT));
                count++;
            }
        }
        closedir(dir);
    }
}
