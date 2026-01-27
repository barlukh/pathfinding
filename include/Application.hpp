/* ************************************************************************************ */
/*                                                                                      */
/*  File:       Application.hpp                                                         */
/*  Purpose:    Header file for the Class Application                                   */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2026/01/27                                                              */
/*                                                                                      */
/* ************************************************************************************ */

#ifndef APPLICATION_H
#define APPLICATION_H

#include "config.hpp"


class Application
{
    private:
        bool windowInitialized = false;
        int screenWidth = 0;
        int screenHeight = 0;
        float gridCellSize = 0.0f;

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

        // Getters & Setters
        float getGridCellSize() const;

        // Member Functions
        static Application::State validateConfig();
        Application::State init();
};

#endif
