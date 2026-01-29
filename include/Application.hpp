/* ************************************************************************************ */
/*                                                                                      */
/*  File:       Application.hpp                                                         */
/*  Purpose:    Header file for the Class Application                                   */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2026/01/28                                                              */
/*                                                                                      */
/* ************************************************************************************ */

#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "Grid.hpp"


class Application
{
    public:
        enum class State
        {
            SUCCESS,
            FAILURE
        };

        // Constructors & Destructors
        Application();
        Application(const Application& other) = delete;
        Application& operator=(const Application& other) = delete;
        ~Application();

        // Member Functions
        State init();
        void run();

    private:
        bool _windowInitialized;
        Grid _grid;
};

#endif
