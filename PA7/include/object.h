#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <fstream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/color4.h>
#include <tinyxml2.h>

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

	ObjectConfig(){
	  name = " ";
	  orbit_speed = 0;
	  orbit_angle = 0;
	  orbit_distance = 2;
	  orbit_direction = 1;
	  orbit_paused = false;
	  rotation_speed = 0;
	  rotation_angle = 0;
	  rotation_direction = 1;
	  rotation_paused = false;
	  scale = 1;
	}
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

    std::vector<Object*> getSatelites();
    void setSatelites(std::vector<Object*> vectors);

    Object* getParent();
    void setParent(Object* p);

    std::string getName();

    void parseObjFile(char* obj_filename);
    void parseObjectConfig(char* object_config_filename);

    glm::mat4 GetModel();
    glm::mat4 GetLocation();

    bool isSelected();
    void Select();
    void Deselect();

    void setScale(float);

  private:
    glm::mat4 model;
    glm::mat4 location;
    bool selected;
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    GLuint VB;
    GLuint IB;
    std::vector<Object*> satelites;
    Object* parent;

    ObjectConfig config;
};

#endif /* OBJECT_H */
