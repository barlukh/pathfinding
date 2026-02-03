/* ************************************************************************************ */
/*                                                                                      */
/*  File:       config.hpp                                                              */
/*  Purpose:    Configuration values used by the application                            */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2026/02/03                                                              */
/*                                                                                      */
/* ************************************************************************************ */

#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <array>
#include <string_view>


namespace conf
{
    // Window
    inline constexpr const std::string_view title = "pathfinding";

    constexpr int gridCellsX = 70;
    constexpr int gridCellsY = 50;
    constexpr int gridPad = 60;
    constexpr int halfPad = gridPad / 2;

    // UI
    constexpr float optScaling = 5.5f;
    constexpr int textScaling = 65;
    constexpr int offsetYScaling = 6;
    constexpr int textSpacing = 5;

    inline constexpr const std::string_view step1 =
        "Step 1 (place cells):\n\n"
        "Press 1 to place Start\n"
        "Press 2 to place End\n"
        "Press 3 to place Obstacles\n"
        "Press 4 to reset Cell\n";

    inline constexpr const std::string_view selection1 =
        "Current selection: ";

    inline constexpr const std::array<std::string_view, 4> opts1 = {
        "Start",
        "End",
        "Obstacles",
        "Empty"
    };

    inline constexpr const std::string_view step2 =
        "Step 2 (select algorithm):\n\n"
        "Press Q to use Flood fill\n"
        "Press W to use A*\n"
        "Press E to use Dijkstra's\n"
        "Press R to use ...";

    inline constexpr const std::string_view selection2 =
        "Current selection: ";

    inline constexpr const std::array<std::string_view, 4> opts2 = {
        "Flood fill",
        "A*",
        "Dijkstra",
        "..."
    };

    // FPS
    constexpr int fps = 1000;
    constexpr bool showFps = true;
}

#endif
