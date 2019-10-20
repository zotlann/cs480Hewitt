#include "object.h"

Object::Object(char* object_config_filename)
{
  //start with model matrix as identity matrix
  model = glm::mat4(1.0f);
  //parse the object's config file
  ParseObjectConfig(object_config_filename);	

  //generate the VB and IB buffers
  glGenBuffers(1, &VB);
  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);

  glGenBuffers(1, &IB);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * Indices.size(), &Indices[0], GL_STATIC_DRAW);
}

Object::~Object()
{
  Vertices.clear();
  Indices.clear();
}

//takes a character representing keyboard input and performs the
//proper mutations on the objects config
void Object::ProcessInput(char input)
{
 switch(input){
  }
}

void Object::Update(unsigned int dt)
{
}

glm::mat4 Object::GetModel()
{
  return model;
}

void Object::Render()
{
  glBindTexture(GL_TEXTURE_2D,texture);

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,texture_coordinates));

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);

  glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
}

//Parses planet config files and creates an object with the proper config settings.
//An example config file can be found in ../assets/entities/planet.conf
void Object::ParseObjectConfig(char* object_config_filename)
{
  
  tinyxml2::XMLDocument doc;
  tinyxml2::XMLError file_loaded = doc.LoadFile(object_config_filename);
  if(file_loaded != tinyxml2::XML_SUCCESS){
    std::string error;
    std::string filename(object_config_filename);
    error  = "XMLError: " + std::to_string(file_loaded) + " in file: " + filename + "\n";
    throw std::logic_error(error);
  }
  
  tinyxml2::XMLElement* object = doc.FirstChildElement("object");
  tinyxml2::XMLElement* element = NULL;

  //set the model
  if((element = object->FirstChildElement("model"))){
    char* filename = new char[256];
    strcpy(filename,element->GetText());
    LoadModel(filename);
    delete filename;
  }

  //set the texture filepath and load the texture
  if((element = object->FirstChildElement("texture"))){
    char* texture_filename = new char[256];
    strcpy(texture_filename,element->GetText());
    LoadTexture(texture_filename);
  }

  //set the scale
  if((element = object->FirstChildElement("scale"))){
    model *= glm::scale(glm::mat4(1.0f),glm::vec3(element->FloatText()));
  }
  //set the initial location
  float x,y,z;
  x = y = z = 0;
  if((element = object->FirstChildElement("location-x"))){
    x = element->FloatText();
  }
  if((element = object->FirstChildElement("location-y"))){
    y = element->FloatText();
  }
  if((element = object->FirstChildElement("location-z"))){
    z = element->FloatText();
  }
  model *= glm::translate(glm::mat4(1.0f),glm::vec3(x,y,z)); 
}

void Object::LoadModel(char* obj_filename)
{
  //set up importer object
  Assimp::Importer importer;
  const aiScene* my_scene = importer.ReadFile(obj_filename, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);
  if(!my_scene){
    throw std::logic_error("Could not open .obj file: " + std::string(obj_filename));
  } 

  //iterate through the meshes and load vertices and indices for each 
  for(unsigned int j = 0; j < my_scene->mNumMeshes; j++){ 
  aiMesh* mesh = my_scene->mMeshes[j];
  //Process Vertices
    for(unsigned int i = 0; i < mesh->mNumVertices; i++){
      aiVector3D ai_vec = mesh->mVertices[i];
      aiVector3D ai_texture = mesh->mTextureCoords[0][i]; 
      glm::vec3 vertex = {ai_vec.x,ai_vec.y,ai_vec.z};
      glm::vec2 texture_coordinates = {ai_texture.x,ai_texture.y};
      Vertices.push_back({vertex,texture_coordinates});
    }
  
  //Process Faces
    for(unsigned int i = 0; i < mesh->mNumFaces; i++){
      aiFace face = mesh->mFaces[i];
    
    //if we were not given triangles throw an error and abort
      if(face.mNumIndices != 3){
        std::string error;
        std::string file_name(obj_filename);
        error = "Expected triangles in faces from file: " + file_name + " but recived " + std::to_string(mesh->mNumFaces) + " indices.\n";
        throw std::logic_error(error);
      }
      Indices.push_back(face.mIndices[0]);
      Indices.push_back(face.mIndices[1]);
      Indices.push_back(face.mIndices[2]);
    }
  }
}

void Object::LoadTexture(char* texture_filepath)
{
  Magick::Image* image;
  Magick::Blob blob;
  GLuint texture;

  //initialize imagemagick
  Magick::InitializeMagick(NULL);

  //load the image data into a blob and bind textures
  image = new Magick::Image(texture_filepath);
  image->write(&blob,"RGBA");
  glGenTextures(1,&texture);
  setTexture(texture);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D,texture);
  glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,image->columns(),image->rows(),-0.5,GL_RGBA,GL_UNSIGNED_BYTE,blob.data());
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  glBindTexture(GL_TEXTURE_2D,0);
}

GLuint Object::getTexture()
{
	return texture;
}

void Object::setTexture(GLuint text)
{
	texture = text;
}
