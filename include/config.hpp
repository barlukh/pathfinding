/* ************************************************************************************ */
/*                                                                                      */
/*  File:       config.hpp                                                              */
/*  Purpose:    Configuration values used by the application                            */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2026/01/27                                                              */
/*                                                                                      */
/* ************************************************************************************ */

#ifndef CONFIG_H
#define CONFIG_H

#include <string_view>


namespace conf
{
    inline constexpr const std::string_view title = "pathfinding";

    constexpr int defaultScreenWidth = 1280;
    constexpr int defaultScreenHeight = 720;

    constexpr int gridCellsX = 50;
    constexpr int gridCellsY = 50;
    constexpr int gridPad = 60;
    constexpr int halfPad = gridPad >> 1;
}

#endif
