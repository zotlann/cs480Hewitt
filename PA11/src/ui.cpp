#include "ui.h"

Ui::Ui(SDL_Window *window, SDL_GLContext context)
{
    // Set up context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    // Initialize opengl and sdl2
    ImGui_ImplSDL2_InitForOpenGL(window, context);
    ImGui_ImplOpenGL3_Init("#version 330");

    // Set up states
    showMainMenu = false;
    showPauseMenu = false;
    showStatistics = true;
    showDeathScreen = false;

    // Set up scoring
    time = 0;
    score = 0;
    lives = 3;
}

Ui::~Ui()
{
    // Clean UI
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

bool Ui::Initialize()
{
    return true;
}

void Ui::Update(KeyHandler* key_handler)
{
    // Pause game
    if(key_handler->IsPressed('p'))
    {
        if(!showPauseMenu)
        {
            showPauseMenu = true;
            key_handler->Unpress('p');
            return;
        }
        else
        {
            showPauseMenu = false;
            key_handler->Unpress('p');
            return;
        }
    }
}

void Ui::Render(SDL_Window* window, unsigned int dt, bool died)
{
    // io
    ImGuiIO& io = ImGui::GetIO(); (void) io;

    // New frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(window);
    ImGui::NewFrame();

    // Score bar
    if(showStatistics)
    {
        // Title bar
        ImGui::Begin("ApeSphere", &showStatistics);
        
        // Time
        ImGui::Text("Time: %.1f", time);
        if(!showPauseMenu && !showDeathScreen)
            time += dt/1000.f;

        // Lives
        if(died)
            lives--;
        ImGui::Text("Lives: %d", lives);

        if(lives == 0)
        {
            showDeathScreen = true;
        }

        // Pause button
        if( ImGui::Button("Pause Menu") )
        {
            if(showPauseMenu)
                showPauseMenu = false;
            else
                showPauseMenu = true;
        }
        ImGui::End();
    }

    if(showPauseMenu)
    {
        ImGui::Begin("Pause", &showPauseMenu);

        //Return to game
        if(ImGui::Button("Return to Game"))
        {
            showPauseMenu = false;
        }

        //Open main menu

        ImGui::End();
    }

    if(showDeathScreen)
    {
        ImGui::Begin("You Died!", &showDeathScreen);

        // Final score
        ImGui::Text("Final time: %.1f", time);

        // Retry
        if(ImGui::Button("Retry Level"))
        {
            lives = 3;
            time = 0;
            score = 0;
            showDeathScreen = false;
        }

        // Go to main menu

        ImGui::End();
    }

    // Render menus
    ImGui::Render();
    glViewport(0,0, (int) io.DisplaySize.x, (int)io.DisplaySize.y);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

bool Ui::GetPauseState()
{
    return showPauseMenu;
}

bool Ui::GetDeathState()
{
    return showDeathScreen;
}