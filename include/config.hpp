/* ************************************************************************************ */
/*                                                                                      */
/*  File:       config.hpp                                                              */
/*  Purpose:    Configuration values used by the application                            */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2026/02/07                                                              */
/*                                                                                      */
/* ************************************************************************************ */

#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <array>
#include <string_view>


namespace conf
{
    // Pathfinding
    constexpr float cellsPerSecond = 500.0f;

    // FPS
    constexpr int fps = 1000;
    constexpr bool showFps = true;

    // Window
    inline constexpr std::string_view title = "pathfinding";

    constexpr int gridCellsX = 70;
    constexpr int gridCellsY = 50;
    constexpr int gridPad = 60;
    constexpr int halfPad = gridPad / 2;

    // UI
    constexpr int textScaling = 65;
    constexpr int textSpacing = 5;
    constexpr int offsetYScaling = 6;

    inline constexpr const std::string_view step1 =
        "Step 1 (place cells):\n\n"
        "Press 1 to place Start\n"
        "Press 2 to place Finish\n"
        "Press 3 to place Wall\n"
        "Press 4 to reset Cell\n";

    inline constexpr const std::string_view selection1 =
        "Current selection: ";

    inline constexpr const std::array<std::string_view, 4> opts1 = {
        "Start",
        "Finish",
        "Wall",
        "Empty"
    };

    inline constexpr const std::string_view step2 =
        "Step 2 (select algorithm):\n\n"
        "Press Q to use DFS FF\n"
        "Press W to use BFS FF\n"
        "Press E to use A*\n"
        "Press R to use Dijkstra's\n";

    inline constexpr const std::string_view selection2 =
        "Current selection: ";

    inline constexpr const std::array<std::string_view, 4> opts2 = {
        "DFS FF",
        "BFS FF",
        "A*",
        "Dijkstra"
    };
}

#endif
