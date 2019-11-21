#include <iostream>

#include "engine.h"

int main(){
	Config* cfg = new Config;
	cfg->window_name = new char[256];
	strcpy(cfg->window_name, "TEST");
	cfg->w = 1024;
	cfg->h = 768;
	cfg->vshader_filename = new char[256];
	strcpy(cfg->vshader_filename, "../assets/shaders/vshader");
	cfg->fshader_filename = new char[256];
	strcpy(cfg->fshader_filename, "../assets/shaders/fshader");

	Engine* engine = new Engine(cfg->window_name, cfg->w, cfg->h);
	if(!engine->Initialize(*cfg)){
		printf("The engine failed to start.\n");
		delete engine;
		engine = NULL;
		return 1;
	}
	engine->Run();
	delete engine;
	engine = NULL;
	return 0;
}
