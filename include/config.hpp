/* ************************************************************************************ */
/*                                                                                      */
/*  File:       config.hpp                                                              */
/*  Purpose:    Configuration values used by the application                            */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2026/02/13                                                              */
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
    constexpr int gridPad = 50;
    constexpr int halfPad = gridPad / 2;

    // UI
    constexpr int textScaling = 65;
    constexpr int textSpacing = 5;
    constexpr int offsetYScaling = 6;

    inline constexpr std::string_view step1 =
        "Step 1 (place cells):\n\n"
        "Press 1 to place Start\n"
        "Press 2 to place Finish\n"
        "Press 3 to place Wall\n"
        "Press 4 to reset Cell\n";

    inline constexpr std::string_view selection1 =
        "Current selection: ";

    inline constexpr std::array<std::string_view, 4> opts1 = {
        "Start",
        "Finish",
        "Wall",
        "Empty"
    };

    inline constexpr std::string_view step2 =
        "Step 2 (select algorithm):\n\n"
        "Press Q to use DFS FF\n"
        "Press W to use BFS FF\n"
        "Press E to use A*\n"
        "Press R to use Dijkstra's\n";

    inline constexpr std::string_view selection2 =
        "Current selection: ";

    inline constexpr std::array<std::string_view, 4> opts2 = {
        "DFS FF",
        "BFS FF",
        "A*",
        "Dijkstra"
    };

    inline constexpr std::string_view step3 =
        "Step 3 (execute / reset):\n\n"
        "Press Space to execute\n"
        "Press C to reset result\n"
        "Press V to reset all\n";

    inline constexpr std::string_view colorIndex =
        "- Start\n"
        "- Finish\n"
        "- Wall\n"
        "- Empty\n"
        "- Visited\n"
        "- Queued\n";
}

#endif
