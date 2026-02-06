/* ************************************************************************************ */
/*                                                                                      */
/*  File:       Application.cpp                                                         */
/*  Purpose:    Source file for the Class Application                                   */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2026/02/06                                                              */
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
:   windowInitialized(false),
    grid(conf::gridCellsX, conf::gridCellsY),
    ui(),
    path()
{
    SetTraceLogLevel(LOG_NONE);
    SetTargetFPS(conf::fps);
}

Application::~Application()
{
    if (windowInitialized)
        CloseWindow();
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
    grid.setGridVec(windowHeight);
    grid.setGridRec();
    ui.calcUIPosValues(grid.getGridRec());

    windowInitialized = true;
    return State::SUCCESS;
}

void Application::run()
{
    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        if (conf::showFps)
            DrawFPS(5, 5);

        // Detect user input
        ui.detectInput();

        // Paint the grid with the selected color
        if (ui.isPaintModeOn())
        {
            ui.setMouseCur(grid.getGridCellSize());

            Grid::Pos p = grid.paint(ui.getS1Key(), ui.getMouseCur(), ui.getMouseLast());
            if (p == Grid::Pos::IN_BOUNDS)
                ui.setMouseLast(ui.getMouseCur());
            else
                ui.setMouseLast({-1, -1});
        }

        // Execute algorithm
        if (ui.isExecModeOn())
            path.execute(ui.getS2Key(), grid.getStartIndex(), grid.updateGridVec());

        // Draw all elements
        ui.drawUI();
        ui.drawGrid(grid.getGridVec(), grid.getGridRec());

        EndDrawing();
    }
}
