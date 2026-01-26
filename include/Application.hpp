/* ************************************************************************************ */
/*                                                                                      */
/*  File:       Application.hpp                                                         */
/*  Purpose:    Header file for the Class Application                                   */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2026/01/26                                                              */
/*                                                                                      */
/* ************************************************************************************ */

#ifndef APPLICATION_H
#define APPLICATION_H

class Application
{
    private:
        int screenWidth;
        int screenHeight;

    public:
        enum class State
        {
            success,
            failure
        };

        Application();
        ~Application();

        Application::State init();
};

#endif
