#include "object.h"

Object::Object()
{  
  /*
    # Blender File for a Cube
    o Cube
    v 1.000000 -1.000000 -1.000000
    v 1.000000 -1.000000 1.000000
    v -1.000000 -1.000000 1.000000
    v -1.000000 -1.000000 -1.000000
    v 1.000000 1.000000 -0.999999
    v 0.999999 1.000000 1.000001
    v -1.000000 1.000000 1.000000
    v -1.000000 1.000000 -1.000000
    s off
    f 2 3 4
    f 8 7 6
    f 1 5 6
    f 2 6 7
    f 7 8 4
    f 1 4 8
    f 1 2 4
    f 5 8 6
    f 2 1 6
    f 3 2 7
    f 3 7 4
    f 5 1 8
  */

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

  //Set Default config settings
  config.orbit_angle = 0;
  config.orbit_speed = 1;
  config.orbit_direction = 1;
  config.orbit_distance = 3;

  config.rotation_angle = 0;
  config.rotation_speed = 1;
  config.rotation_direction = 1;
  config.scale = 1;
}

Object::Object(char* object_config_filename)
{  
  /*
    # Blender File for a Cube
    o Cube
    v 1.000000 -1.000000 -1.000000
    v 1.000000 -1.000000 1.000000
    v -1.000000 -1.000000 1.000000
    v -1.000000 -1.000000 -1.000000
    v 1.000000 1.000000 -0.999999
    v 0.999999 1.000000 1.000001
    v -1.000000 1.000000 1.000000
    v -1.000000 1.000000 -1.000000
    s off
    f 2 3 4
    f 8 7 6
    f 1 5 6
    f 2 6 7
    f 7 8 4
    f 1 4 8
    f 1 2 4
    f 5 8 6
    f 2 1 6
    f 3 2 7
    f 3 7 4
    f 5 1 8
  */

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

  //Pares an object config file and makes the appropriate assignments to the config
  parseObjectConfig(object_config_filename);
}

Object::~Object()
{
  Vertices.clear();
  Indices.clear();
}

void Object::processInput(char input){
 switch(input){
    case 'a':
      config.rotation_direction *= -1;
      break;
    case 's':
      config.orbit_direction *= -1;
      break;
    case 'd':
      config.rotation_speed *= 1.1;
      break;
    case 'f':
      config.rotation_speed /= 1.1;
      break;
    case 'g':
      config.orbit_speed *= 1.1;
      break;
    case 'h':
      config.orbit_speed /= 1.1;
      break;
  }
}

void Object::Update(unsigned int dt)
{
  config.rotation_angle += dt * M_PI/1000;
  config.orbit_angle += dt * M_PI/1000;
  float orbit_angle = config.orbit_angle * config.orbit_speed * config.orbit_direction;
  float rotation_angle = config.rotation_angle * config.rotation_speed * config.rotation_direction;
  glm::mat4 orbit;
  glm::mat4 rotation;
  orbit = glm::rotate(glm::mat4(1.0f),orbit_angle,glm::vec3(0.0,1.0,0.0)); 
  orbit *= glm::translate(glm::mat4(1.0f),glm::vec3(config.orbit_distance,0.0,0.0));
  rotation = glm::rotate(glm::mat4(1.0f),rotation_angle,glm::vec3(0.0,1.0,0.0));
  model = orbit * rotation;
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

void Object::parseObjectConfig(char* object_config_filename){
  std::string temp_string;
  float temp_float;

  std::ifstream config_file;
  config_file.open(object_config_filename);
  if(!config_file.good()){
    printf("Invalid object config filepath: %s\n",object_config_filename);
    return;
  }

  while(!config_file.eof()){
    config_file >> temp_string;
    if(temp_string == "Planet"){
      config_file >> temp_string;
      config_file >> temp_string;
      config.name = temp_string;
    }
    else if(temp_string == "Orbit"){
      config_file >> temp_string;
      if(temp_string == "Speed:"){
        config_file >> temp_float;
	config.orbit_speed = temp_float;
      }
      else if(temp_string == "Direction:"){
        config_file >> temp_string;
	if(temp_string == "Clockwise"){
	  config.orbit_direction = 1;
	}
	else{
	  config.orbit_direction = -1;
	}
      }
      else if(temp_string == "Distance:"){
        config_file >> temp_float;
	config.orbit_distance = temp_float;
      }
      else{
        std::cout << "Invalid config option Orbit " << temp_string << std::endl;
	std::cout << "In: " << object_config_filename << std::endl;
      }
      std::getline(config_file,temp_string);
    }
    else if(temp_string == "Rotation"){
      config_file >> temp_string;
      if(temp_string == "Speed:"){
        config_file >> temp_float;
	config.rotation_speed = temp_float;
      }
      else if(temp_string == "Direction:"){
        config_file >> temp_string;
	if(temp_string == "Clockwise"){
	  config.rotation_direction = 1;
	}
	else{
	  config.rotation_direction = -1;
	}
      }
      else{
        std::cout << "Invalid config option Rotation " << temp_string << std::endl;
	std::cout << "In: " << object_config_filename << std::endl;
      }
      std::getline(config_file,temp_string);
    }
    else if(temp_string == "Scale:"){
      config_file >> temp_float;
      config.scale = temp_float;
      std::getline(config_file,temp_string);
    }
    else{
      std::cout << "Invalid config option " << temp_string << std::endl;
      std::getline(config_file,temp_string);
      std::cout << temp_string << std::endl;
      std::cout <<"In: " << object_config_filename << std::endl;
      std::getline(config_file,temp_string);
    }
  }
  config.orbit_angle = 2 * M_PI;
  config.rotation_angle = 2 * M_PI;
  config_file.close();
  std::cout << "NAME: " << config.name << std::endl;
  std::cout << "SCALE: " << config.scale << std::endl;
  std::cout << "ORBIT SPEED: " << config.orbit_speed << std::endl;
  std::cout << "ORBIT DIRECTION: " << config.orbit_direction << std::endl;
  std::cout << "ORBIT ANGLE: " << config.orbit_angle << std::endl;
  std::cout << "ORBIT DISTANCE: " << config.orbit_distance << std::endl;
  std::cout << "ROTATION SPEED: " << config.rotation_speed << std::endl;
  std::cout << "ROTATION DIRECTION: " << config.rotation_direction << std::endl;
  std::cout << "ROTATION ANGLE: " << config.rotation_angle << std::endl;
}

