/* ************************************************************************************ */
/*                                                                                      */
/*  File:       config.hpp                                                              */
/*  Purpose:    Configuration values used by the application                            */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2026/01/30                                                              */
/*                                                                                      */
/* ************************************************************************************ */

#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string_view>


namespace conf
{
    inline constexpr const std::string_view title = "pathfinding";

    constexpr int gridCellsX = 70;
    constexpr int gridCellsY = 50;
    constexpr int gridPad = 60;
    constexpr int halfPad = gridPad / 2;

    constexpr int fps = 60;
    constexpr bool showFps = true;
}

#endif
