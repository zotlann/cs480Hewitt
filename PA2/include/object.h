#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <fstream>
#include "graphics_headers.h"
#include "assets.h"

struct ObjectConfig{
	std::string name;

	float orbit_speed;
	float orbit_angle;
	int orbit_direction;
	float orbit_distance;
	bool orbit_paused;

	float rotation_speed;
	float rotation_angle;
	int rotation_direction;
	bool rotation_paused;

	float scale;
};

class Object
{
  public:
    Object();
    Object(char* object_config_filename);
    ~Object();
    void Update(unsigned int dt);
    void processInput(char input);
    void Input(char input);
    void Render();

    void parseObjectConfig(char* object_config_filename);

    glm::mat4 GetModel();

  private:
    glm::mat4 model;
    glm::mat4 prev_model;
    bool prev_model_set;
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    GLuint VB;
    GLuint IB;

    ObjectConfig config;
};

#endif /* OBJECT_H */
