/* ************************************************************************************ */
/*                                                                                      */
/*  File:       main.cpp                                                                */
/*  Purpose:    Main source file and the starting point of the program                  */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2026/01/26                                                              */
/*                                                                                      */
/* ************************************************************************************ */

#include "constants.hpp"
#include <iostream>

int main()
{
    std::cout << constants::failure;

    std::cout << "hello ";
    std::cout << "world";
    std::cout << std::endl;

    return EXIT_SUCCESS;
}
