#include "ui.h"

Ui::Ui(SDL_Window *window, SDL_GLContext context)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplSDL2_InitForOpenGL(window, context);
    ImGui_ImplOpenGL3_Init("#version 330");

    showMainMenu = false;
    showPauseMenu = false;
    showStatistics = true;

    time = 0;
    score = 0;
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

void Ui::Render(SDL_Window* window, unsigned int dt)
{
    ImGuiIO& io = ImGui::GetIO(); (void) io;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(window);
    ImGui::NewFrame();

    // Score bar
    if(showStatistics)
    {
        ImGui::Begin("ApeSphere", &showStatistics);
        // Time
        ImGui::Text("Time: %.1f", time);
        time += dt/1000.f;

        // Pause button
        if( ImGui::Button("Pause") )
        {
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

    // Render menus
    ImGui::Render();
    glViewport(0,0, (int) io.DisplaySize.x, (int)io.DisplaySize.y);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

bool Ui::GetPauseState()
{
    return showPauseMenu;
}