#include "ui.h"

Ui::Ui(SDL_Window *window, SDL_GLContext context)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void) io;
    ImGui::StyleColorsDark();

    ImGui_ImplSDL2_InitForOpenGL(window, context);
    ImGui_ImplOpenGL3_Init("#version 330");

    showMainMenu = false;
    showPauseMenu = false;
    showStatistics = true;
}

Ui::~Ui()
{

}

bool Ui::Initialize()
{
    return true;
}

void Ui::Update(KeyHandler* key_handler)
{
    if(key_handler->IsPressed('p'))
    {
        if(showStatistics)
        {
            showStatistics = false;
            showPauseMenu = true;
            key_handler->Unpress('p');
            return;
        }
        else
        {
            showStatistics = true;
            showPauseMenu = false;
            key_handler->Unpress('p');
            return;
        }
    }
}

void Ui::Render()
{

}

bool Ui::GetStatisticState()
{
    return showStatistics;
}