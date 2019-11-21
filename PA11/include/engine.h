#ifndef ENGINE_H
#define ENGINE_H

#include <sys/time.h>
#include <assert.h>

#include "window.h"
#include "graphics.h"

class Engine{
	public:
		Engine(char* name, int w, int h);
		Engine(char* name);
		~Engine();
		bool Initialize(Config cfg);
		void Run();
		char Keyboard();
		char Mouse();
		glm::vec2 MouseMovement();
		unsigned int GetDT();
		long long GetCurrentTimeMillis();
	private:
		//Window related variables
		Window* window;
		char* window_name;
		int window_width;
		int window_height;
		bool is_fullscreen;
		SDL_Event event;

		Graphics* graphics;
		unsigned int DT;
		long long current_time_millis;
		bool is_running;
};

#endif //ENGINE_H
