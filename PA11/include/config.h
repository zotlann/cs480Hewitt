//--------------------------------------------------------------------
//
// config.h
// Config struct containing any meta config information, such as
// window sizing and naming
//
//--------------------------------------------------------------------

#ifndef CONFIG_H
#define CONFIG_H

struct Config{
	char* window_name;
	char* vshader_filename;
	char* fshader_filename;
	int w;
	int h;
};

#endif //CONFIG_H
