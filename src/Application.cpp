/* ************************************************************************************ */
/*                                                                                      */
/*  File:       Application.cpp                                                         */
/*  Purpose:    Source file for the Class Application                                   */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2026/01/27                                                              */
/*                                                                                      */
/* ************************************************************************************ */

#include "Application.hpp"
#include "config.hpp"
#include "raylib.h"
#include <iostream>
#include <string_view>


//----------------------------------------------------------------------------------------
// Constructors & Destructors
//----------------------------------------------------------------------------------------

Application::Application()
{
    SetTraceLogLevel(LOG_NONE);
}

Application::~Application()
{
    if (windowInitialized)
    {
        CloseWindow();
    }
}


//----------------------------------------------------------------------------------------
// Getters & Setters
//----------------------------------------------------------------------------------------

float Application::getGridCellSize() const
{
    return gridCellSize;
}


//----------------------------------------------------------------------------------------
// Member Functions
//----------------------------------------------------------------------------------------

Application::State Application::validateConfig()
{
    if (conf::title.size() < 1 || conf::title.size() > 20)
    {
        std::cerr   << "Invalid conf:\n"
                    << "   title = " << conf::title
                    << " (allowed length: 1-20 characters)\n";
        return State::FAILURE;
    }

    if ((conf::defaultScreenWidth <= 0 || conf::defaultScreenWidth > 3840)
        || (conf::defaultScreenHeight <= 0 || conf::defaultScreenHeight > 2160))
    {
        std::cerr   << "Invalid conf:\n"
                    << "   defaultScreenWidth = " << conf::defaultScreenWidth
                    << " (allowed range: 1-3840)\n"
                    << "   defaultScreenHeight = " << conf::defaultScreenHeight
                    << " (allowed range: 1-2160)\n";
        return State::FAILURE;
    }

    if ((conf::gridCellsX <= 0 || conf::gridCellsX > 100)
        || (conf::gridCellsY <= 0 || conf::gridCellsY > 100))
    {
        std::cerr   << "Invalid conf:\n"
                    << "   gridCellsX = " << conf::gridCellsX
                    << " (allowed range: 1-100)\n"
                    << "   gridCellsY = " << conf::gridCellsY
                    << " (allowed range: 1-100)\n";
        return State::FAILURE;
    }

    if ((conf::gridCellsX != conf::gridCellsY))
    {
        std::cerr   << "Invalid conf:\n"
                    << "   gridCellsX = " << conf::gridCellsX
                    << " (must equal to gridCellsY)\n"
                    << "   gridCellsY = " << conf::gridCellsY
                    << " (must equal to gridCellsX)\n";
        return State::FAILURE;
    }

    if ((conf::gridPad <= 0 || conf::gridPad > 200))
    {
        std::cerr   << "Invalid conf:\n"
                    << "   gridPad = " << conf::gridPad
                    << " (allowed range: 1-200)\n";
        return State::FAILURE;
    }

    return State::SUCCESS;
}

Application::State Application::init()
{
    InitWindow(conf::defaultScreenWidth, conf::defaultScreenHeight, conf::title.data());
    if (!IsWindowReady())
    {
        return State::FAILURE;
    }

    windowInitialized = true;
    
    int monitor = GetCurrentMonitor();
    screenWidth = GetMonitorWidth(monitor);
    screenHeight = GetMonitorHeight(monitor);

    SetWindowSize(screenWidth, screenHeight);
    ToggleFullscreen();

    gridCellSize = (static_cast<float>(screenHeight - conf::gridPad) / conf::gridCellsY);

    return State::SUCCESS;
}
