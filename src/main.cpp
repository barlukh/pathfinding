/* ************************************************************************************ */
/*                                                                                      */
/*  File:       main.cpp                                                                */
/*  Purpose:    Main source file and the starting point of the application              */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2026/01/28                                                              */
/*                                                                                      */
/* ************************************************************************************ */

#include "Application.hpp"
#include <stdlib.h>


int main()
{
    Application app;

    if (app.init() != Application::State::SUCCESS)
        return EXIT_FAILURE;

    app.run();

    return EXIT_SUCCESS;
}
