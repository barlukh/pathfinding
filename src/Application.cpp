/* ************************************************************************************ */
/*                                                                                      */
/*  File:       Application.cpp                                                         */
/*  Purpose:    Source file for the Class Application                                   */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2026/02/04                                                              */
/*                                                                                      */
/* ************************************************************************************ */

#include "Application.hpp"
#include "Grid.hpp"
#include "UI.hpp"
#include "Pathfinding.hpp"
#include "config.hpp"
#include "raylib.h"
#include <iostream>
#include <string_view>


//----------------------------------------------------------------------------------------
// Constructors & Destructors
//----------------------------------------------------------------------------------------

Application::Application()
:   _windowInitialized(false),
    _grid(conf::gridCellsX, conf::gridCellsY),
    _ui(),
    _path()
{
    SetTraceLogLevel(LOG_NONE);
    SetTargetFPS(conf::fps);
}

Application::~Application()
{
    if (_windowInitialized)
    {
        CloseWindow();
    }
}


//----------------------------------------------------------------------------------------
// Member Functions
//----------------------------------------------------------------------------------------

Application::State Application::init()
{
    InitWindow(1, 1, conf::title.data());
    if (!IsWindowReady())
    {
        std::cerr << "Error initializing window\n";
        return State::FAILURE;
    }

    // Measure monitor and derive window size
    int monitor = GetCurrentMonitor();
    int screenWidth = GetMonitorWidth(monitor);
    int screenHeight = GetMonitorHeight(monitor);
    int windowWidth = screenWidth / 1.2;
    int windowHeight = screenHeight / 1.2;
    int windowPosX = (screenWidth - windowWidth) / 2;
    int windowPosY = (screenHeight - windowHeight) / 2;

    SetWindowSize(windowWidth, windowHeight);
    SetWindowPosition(windowPosX, windowPosY);

    // Create grid and set UI position
    _grid.setGridVec(windowHeight);
    _grid.setGridRec();
    _ui.setTextPos(_grid.getGridRec());

    _windowInitialized = true;
    return State::SUCCESS;
}

void Application::run()
{
    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        if (conf::showFps)
        {
            DrawFPS(5, 5);
        }

        // Detect user input
        _ui.detectInput(_grid.getLastGridX(), _grid.getLastGridY());

        if (_ui.getPaintMode())
        {
            _grid.paintCells(_ui.getPaintKey());
        }

        if (IsKeyPressed(KEY_SPACE))
        {
            _path.floodFill(_grid.getGridVec(), conf::gridCellsX, conf::gridCellsY, 0, 0);
            _grid.setDrawFlag(true);
        }

        if (_grid.drawFlag())
        {
            _grid.setGridCell(_path.getFloodFillOrder());
        }

        // Draw all elements
        _grid.drawGrid();
        _ui.drawUI();

        EndDrawing();
    }
}
