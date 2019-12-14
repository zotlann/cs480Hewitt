#ifndef UI_H_
#define UI_H_

#include "imgui.h"
#include <stdio.h>
#include <SDL2/SDL.h>
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"
#include "graphics_headers.h"
#include "keyhandler.h"

class Ui
{
    public:
        Ui(SDL_Window* window, SDL_GLContext context);
        ~Ui();
        bool Initialize();
        void Update(KeyHandler* key_handler);
        void Render(SDL_Window* window, unsigned int dt, bool died, bool& quit, bool &reset);
        bool GetPauseState();
        bool GetDeathState();
        bool GetMainMenuState();
        bool GetConfirmState();
        bool GetTimeOutState();

    private:
        SDL_GLContext gl_context;
        
        // States of windows
        bool showMainMenu;
        bool showTimeOut;
        bool showPauseMenu;
        bool showStatistics;
        bool showDeathScreen;
        bool showConfirmQuit;

        float time;
        int score;
        int lives;
};

#endif