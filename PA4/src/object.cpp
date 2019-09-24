#include "object.h"

Object::Object()
{ 
  Vertices = {
    {{1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 0.0f}},
    {{1.0f, -1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},
    {{-1.0f, -1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},
    {{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 1.0f}},
    {{1.0f, 1.0f, -1.0f}, {1.0f, 1.0f, 0.0f}},
    {{1.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 1.0f}},
    {{-1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 1.0f}},
    {{-1.0f, 1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}}
  };
  Indices = {
    2, 3, 4,
    8, 7, 6,
    1, 5, 6,
    2, 6, 7,
    7, 8, 4,
    1, 4, 8,
    1, 2, 4,
    5, 8, 6,
    2, 1, 6,
    3, 2, 7,
    3, 7, 4,
    5, 1, 8
  };

  // The index works at a 0th index
  for(unsigned int i = 0; i < Indices.size(); i++)
  {
    Indices[i] = Indices[i] - 1;
  }
  glGenBuffers(1, &VB);
  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);
  glGenBuffers(1, &IB);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * Indices.size(), &Indices[0], GL_STATIC_DRAW);
  parent = NULL;
}

Object::Object(char* object_config_filename,char* obj_filename,float scl)
{  
  parseObjFile(obj_filename);
  // The index works at a 0th index
  for(unsigned int i = 0; i < Indices.size(); i++)
  {
    Indices[i] = Indices[i] - 1;
  }

  glGenBuffers(1, &VB);
  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);

  glGenBuffers(1, &IB);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * Indices.size(), &Indices[0], GL_STATIC_DRAW);

  //Parse an object config file and makes the appropriate assignments to the config
  config = parseObjectConfig(object_config_filename);
  if(scl > 0.0){
    config.scale = scl;
  }
}

Object::~Object()
{
  Vertices.clear();
  Indices.clear();
}

//takes a character representing keyboard input and performs the
//proper mutations on the objects config
void Object::processInput(char input){
 switch(input){
    case 'q':
      config.rotation_direction *= -1;
      break;
    case 'w':
      config.rotation_speed -= 0.5;
      break;
    case 'e':
      config.rotation_speed += 0.5;
      break;
    case 'r':
      if(config.rotation_paused){
        config.rotation_paused = false;
      }
      else{
        config.rotation_paused = true;
      }
      break;
    case 'a':
      config.orbit_direction *= -1;
      break;
    case 's':
      config.orbit_speed -= 0.5;
      break;
    case 'd':
      config.orbit_speed += 0.5;
      break;
    case 'f':
      if(config.orbit_paused){
        config.orbit_paused = false;
      }
      else{
        config.orbit_paused = true;
      } 
      break;
    case 'z':
      config.orbit_distance /= 1.1;
      break;
    case 'x':
      config.orbit_distance *= 1.1;
      break;
    case 'c':
      config.scale /= 1.1;
      break;
    case 'v':
      config.scale *= 1.1;
      break;
    default:
      break;
  }
}

void Object::Update(unsigned int dt)
{
  model = glm::scale(glm::mat4(1.0f),glm::vec3(config.scale));
  /*
  //If rotation/orbit are not paused, increment the angles.
  if(!config.orbit_paused){
    if(config.orbit_direction > 0){
      config.orbit_angle += dt * (M_PI + config.orbit_speed)/1000;
    }
    else{
      config.orbit_angle -= dt * (M_PI + config.orbit_speed)/1000;
    }
  }
  if(!config.rotation_paused){
    if(config.rotation_direction > 0){
      config.rotation_angle += dt * (M_PI + config.rotation_speed)/1000;
    }
    else{
      config.rotation_angle -= dt * (M_PI + config.orbit_speed)/1000;
    }
  }
  //Calculate the final angles with all scalars.
  float orbit_angle = config.orbit_angle;
  float rotation_angle = config.rotation_angle;

  glm::mat4 orbit;
  glm::mat4 rotation;
  glm::mat4 scale;
  
  //perform the rotations and translations
  orbit = glm::rotate(glm::mat4(1.0f),orbit_angle,glm::vec3(0.0,1.0,0.0)); 
  orbit *= glm::translate(glm::mat4(1.0f),glm::vec3(config.orbit_distance,0.0,0.0));
  orbit *= glm::rotate(glm::mat4(1.0f),-orbit_angle,glm::vec3(0.0,1.0,0.));
  location = orbit;
  rotation = glm::rotate(glm::mat4(1.0f),rotation_angle,glm::vec3(0.0,1.0,0.0));
  scale = glm::scale(glm::mat4(1.0f),glm::vec3(config.scale));
  if(parent != NULL){
    model = parent->GetLocation() * orbit * rotation * scale;
  }
  else{
    model = orbit * rotation * scale;
  }*/
}

glm::mat4 Object::GetModel()
{
  return model;
}

void Object::Render()
{
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,color));

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);

  glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
}

//Parses planet config files and creates an object with the proper config settings.
//An example config file can be found in ../assets/entities/planet.conf
ObjectConfig Object::parseObjectConfig(char* object_config_filename){
  std::string temp_string;
  float temp_float;
  
  std::ifstream config_file;
  config_file.open(object_config_filename);
  if(!config_file.good()){
    printf("Invalid object config filepath: %s\nUsing default object config.\n",object_config_filename);
    return ObjectConfig();
  }

}

void Object::parseObjFile(char* obj_filename){
  std::string line_header;
  std::string temp_string;
  unsigned int x,y,z;

  std::ifstream obj_file;
  obj_file.open(obj_filename);
  if(!obj_file.good()){
    std::string error = "Invalid .obj file: ";
    temp_string = std::string(obj_filename);
    error = error + temp_string + "aborting.\n";
    throw std::logic_error(error);
  }
  int i = 0;
  while(!obj_file.eof()){
    obj_file >> line_header;
    
    //ignore any whitespace
    while(obj_file.peek() == ' ' || obj_file.peek() == '\n'){
      obj_file.get();
    }

    //ignore lines with comments
    if(line_header[0] == '#' || line_header[0] == 'o' || line_header[0] == 's'){
      std::getline(obj_file,temp_string);
    }
    //read and push vertex to Vertices
    else if(line_header == "v"){
      glm::vec3 vertex;
      glm::vec3 color;
      if(Vertices.size() % 2 == 0){
        color = {0.0,0.0,1.0};
      }
      else{
	color = {0.2,0.5,0.5};
      }
      obj_file >> vertex.x; obj_file >> vertex.y; obj_file >> vertex.z;
      Vertices.push_back({vertex,color});
      std::getline(obj_file,temp_string);
    }
    //read and push indices
    else if(line_header == "f"){
      std::getline(obj_file,temp_string);
      std::stringstream ss(temp_string);
      if((temp_string.find("//") != std::string::npos) || (temp_string.find("/") != std::string::npos)){
        ss >> x; ss >> temp_string; ss >> y; ss >> temp_string; ss >> z;
      }
      else if(temp_string.find("/") != std::string::npos){
        ss >> x; ss >> temp_string; ss >> y; ss >> temp_string; ss >> z;
      }
      else{
	ss >> x; ss >> y; ss >> z;
      }
      Indices.push_back(x); Indices.push_back(y); Indices.push_back(z);
    }
    //Ignore lines starting with s because I don't know what that does.
    else if(line_header == "s"){
      std::getline(obj_file,temp_string);
    } 
    else{
      std::getline(obj_file,temp_string);
   } 
  }
}
      
    
 

std::vector<Object*> Object::getSatelites(){
  return satelites;
}

void Object::setSatelites(std::vector<Object*> s){
  satelites = s;
}

Object* Object::getParent(){
  return parent;
}

void Object::setParent(Object* p){
  parent = p;
}

glm::mat4 Object::GetLocation(){
  return location;
}

bool Object::isSelected(){
  return selected;
}
void Object::Select(){
  selected = true;
}
void Object::Deselect(){
  selected = false;
}

void Object::setScale(float s){
  config.scale = s;
}
