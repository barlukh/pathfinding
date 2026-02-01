/* ************************************************************************************ */
/*                                                                                      */
/*  File:       config.hpp                                                              */
/*  Purpose:    Configuration values used by the application                            */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2026/02/01                                                              */
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
    constexpr int offsetYScaling = 7;

    inline constexpr const std::string_view step1 =
        "Step 1:\n\n"
        "Press 1 to place Player\n"
        "Press 2 to place Goal\n"
        "Press 3 to place Obstacles\n";

    inline constexpr const std::string_view selection =
        "Current selection: ";

    inline constexpr const std::array<std::string_view, 3> opts = {
        "Player",
        "Goal",
        "Obstacles"
    };

    // FPS
    constexpr int fps = 1000;
    constexpr bool showFps = true;
}

#endif
