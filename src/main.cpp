/* ************************************************************************************ */
/*                                                                                      */
/*  File:       main.cpp                                                                */
/*  Purpose:    Main source file and the starting point of the application              */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2026/01/27                                                              */
/*                                                                                      */
/* ************************************************************************************ */

#include "Application.hpp"
#include "config.hpp"
#include "raylib.h"
#include <stdlib.h>


int main()
{
    if (Application::validateConfig() != Application::State::SUCCESS)
        return EXIT_FAILURE;

    Application app;

    if (app.init() != Application::State::SUCCESS)
        return EXIT_FAILURE;

    float gridCellSize = app.getGridCellSize();

    while (!WindowShouldClose())
    {
        BeginDrawing();
        
        ClearBackground(RAYWHITE);

        DrawRectangle(conf::halfPad, conf::halfPad, conf::gridCellsX * gridCellSize, conf::gridCellsY * gridCellSize, LIGHTGRAY);

        for (size_t y = 0; y <= conf::gridCellsY; y++)
        {
            DrawLine(
                conf::halfPad,
                conf::halfPad + y * gridCellSize,
                conf::halfPad + conf::gridCellsX * gridCellSize,
                conf::halfPad + y * gridCellSize,
                BLACK
            );
        }

        for (size_t x = 0; x <= conf::gridCellsX; x++)
        {
            DrawLine(
                conf::halfPad + x * gridCellSize,
                conf::halfPad,
                conf::halfPad + x * gridCellSize,
                conf::halfPad + conf::gridCellsY * gridCellSize,
                BLACK
            );
        }

        EndDrawing();
    }

    return EXIT_SUCCESS;
}
