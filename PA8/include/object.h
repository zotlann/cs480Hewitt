#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <fstream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/color4.h>
#include <tinyxml2.h>
#include <Magick++.h>
#include <btBulletDynamicsCommon.h>

#include "graphics_headers.h"
#include "assets.h"

class Object
{
  public:
    Object(char* object_config_filename);
    ~Object();
    void Update(unsigned int dt);
    void ProcessInput(char input);
    void Render();

    void LoadModel(char* obj_filename);
    void ParseObjectConfig(char* object_config_filename);
    void LoadTexture(char* texture_filepath);

    GLuint getTexture();
    void setTexture(GLuint text);

    glm::mat4 GetModel();
  
  private:
    glm::mat4 model;
    
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    GLuint VB;
    GLuint IB;
    GLuint texture;
};

#endif /* OBJECT_H */
