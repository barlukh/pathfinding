/* ************************************************************************************ */
/*                                                                                      */
/*  File:       Application.hpp                                                         */
/*  Purpose:    Header file for the Class Application                                   */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2026/02/01                                                              */
/*                                                                                      */
/* ************************************************************************************ */

#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "Grid.hpp"
#include "UI.hpp"


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
        UI _ui;
};

#endif
