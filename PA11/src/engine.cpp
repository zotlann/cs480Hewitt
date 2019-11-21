#include "engine.h"

Engine::Engine(char* name, int w, int h){
	window_name = name;
	window_width = w;
	window_height = h;
	is_fullscreen = false;
}

Engine::Engine(char* name){
	window_name = name;
	window_width = 0;
	window_height = 0;
	is_fullscreen = true;
}

Engine::~Engine(){
	delete window;
	delete graphics;
	window = NULL;
	graphics = NULL;
}

bool Engine::Initialize(Config cfg){
	//Start a window
	window = new Window();
	if(!window->Initialize(window_name,&window_width,&window_height)){
		printf("The window failed to initialize.\n");
		return false;
	}
	//Start the graphics
	graphics = new Graphics();
	if(!graphics->Initialize(window_width,window_height,cfg)){
		printf("The graphics failed to initialize.\n");
		return false;
	}

	//Set the time
	current_time_millis = GetCurrentTimeMillis();

	return true;
}

void Engine::Run(){
	char input = '\0';
	is_running = true;
	while(is_running){
		//Update the DT
		DT = GetDT();
		//Check the keyboard input
		while(SDL_PollEvent(&event) != 0){
			input = Keyboard() | Mouse();
			if(input) break;
		}
		//Update and render the graphics
		graphics->Update(DT,input);
		graphics->Render();
		input = '\0';

		//Swap to the Window
		window->Swap();
	}
}

char Engine::Mouse(){
	if(event.type == SDL_QUIT){
		is_running = false;
		return '\0';
	}
	else if(event.type == SDL_MOUSEBUTTONDOWN){
		switch(event.button.button){
			case SDL_BUTTON_LEFT:
				return 1;
				break;
			case SDL_BUTTON_RIGHT:
				return 2;
				break;
			case SDL_BUTTON_MIDDLE:
				return 3;
				break;
			default:
				return '\0';
				break;
			}
	}
	return '\0';
}

char Engine::Keyboard(){
	if(event.type == SDL_QUIT){
		is_running = false;
		return '\0';
	}
	else if(event.type == SDL_KEYDOWN){
		switch(event.key.keysym.sym){
			case SDLK_ESCAPE:
				printf("Exiting Program\n");
				is_running = false;
				break;
			case SDLK_w:
				return 'w';
				break;
			case SDLK_a:
				return 'a';
				break;
			case SDLK_s:
				return 's';
				break;
			case SDLK_d:
				return 'd';
				break;
			default:
				return '\0';
				break;
		}
	}
	return '\0';
}

unsigned int Engine::GetDT(){
	long long TimeNowMillis = GetCurrentTimeMillis();
	assert(TimeNowMillis >= current_time_millis);
	unsigned int DeltaTimeMillis = (unsigned int)(TimeNowMillis - current_time_millis);
	current_time_millis = TimeNowMillis;
	return DeltaTimeMillis;
}

long long Engine::GetCurrentTimeMillis(){
	timeval t;
	gettimeofday(&t, NULL);
	long long ret = t.tv_sec * 1000 + t.tv_usec / 1000;
	return ret;
}
