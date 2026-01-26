/* ************************************************************************************ */
/*                                                                                      */
/*  File:       Application.cpp                                                         */
/*  Purpose:    Source file for the Class Application                                   */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2026/01/26                                                              */
/*                                                                                      */
/* ************************************************************************************ */

#include "Application.hpp"
#include "config.hpp"
#include "raylib.h"

Application::Application()
{
    SetTargetFPS(config::fps);
}

Application::~Application()
{}

Application::State Application::init()
{
    if (config::defaultWidth <= 0 || config::defaultHeight <= 0)
    {
        return State::failure;
    }

    InitWindow(config::defaultWidth, config::defaultHeight, config::title);
    if (!IsWindowReady())
    {
        return State::failure;
    }

    ToggleBorderlessWindowed();
    DisableCursor();

    int currentMonitor = GetCurrentMonitor();
    screenWidth = GetMonitorWidth(currentMonitor);
    screenHeight = GetMonitorHeight(currentMonitor);

    if (screenWidth <= 0 || screenHeight <= 0)
    {
        CloseWindow();
        return State::failure;
    }

    return State::success;
}
