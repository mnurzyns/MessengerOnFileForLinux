#pragma once
#include <queue>
#include <memory>
#include <ncurses.h>
#include <atomic>

#include <Logger.hpp>
#include <LogSpace.hpp>

namespace ConsoleWindow
{
    static std::atomic<int> terminalSizeX;
    static std::atomic<int> terminalSizeY;

    void displayMainWindow();
    void displayRegistrationWindow();
    void displayLoggedWindow();
    void updateTerminalSize();
    std::string getStringFromConsoleWindow();
}