#include "object.h"

Object::Object(btDiscreteDynamicsWorld* dynamics_world)
{
  Vertices = {
    {{1.0f, -1.0f, -1.0f}, {0.0f, 0.0f}},
    {{1.0f, -1.0f, 1.0f}, {1.0f, 0.0f}},
    {{-1.0f, -1.0f, 1.0f}, {0.0f, 1.0f}},
    {{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f}},
    {{1.0f, 1.0f, -1.0f}, {1.0f, 1.0f}},
    {{1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},
    {{-1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},
    {{-1.0f, 1.0f, -1.0f}, {1.0f, 1.0f}}
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

  btVector3 vec = {1,1,1};
  shape = new btBoxShape(vec);

  glGenBuffers(1, &VB);
  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);

  glGenBuffers(1, &IB);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * Indices.size(), &Indices[0], GL_STATIC_DRAW);

  btTransform startTransform;
  startTransform.setIdentity();
  btScalar mass = btScalar(10000);
  bool isDynamic = (mass != 0.0f);

  btVector3 localInertia(0,0,0);
  if( isDynamic )
    shape->calculateLocalInertia(mass, localInertia);

  startTransform.setOrigin(btVector3(0, 4, 4));
  shapeMotionState = new btDefaultMotionState(startTransform);
  btRigidBody::btRigidBodyConstructionInfo rigid_body_information(mass,shapeMotionState,shape,localInertia);
  //rigid_body_information.m_restitution = cfg.restitution;
  //rigid_body_information.m_friction = 0;
  body = new btRigidBody(rigid_body_information);
  //body->activate(true);
  //body->setActivationState(DISABLE_DEACTIVATION);
  std::cout << "Am I dynamic? " << std::boolalpha << isDynamic << std::endl;
  dynamics_world->addRigidBody(body);
}

Object::Object(char* object_config_filename, btDiscreteDynamicsWorld *dynamics_world)
{
  //start with model matrix as identity matrix
  model = glm::mat4(1.0f);

  //parse the object's config file
  ParseObjectConfig(object_config_filename);

  //load the objects collision shape
  LoadShape(cfg.shape);

  //sets up rigidBody information
  //TODO
  //put this into a LoadBody Function
  btTransform startTransform;
  startTransform.setIdentity();
  btScalar mass = btScalar(cfg.mass);
  bool isDynamic = (mass != 0.0f);

  btVector3 localInertia(0,0,0);
  if( isDynamic )
    shape->calculateLocalInertia(mass, localInertia);

  startTransform.setOrigin(btVector3(location.x, location.y, location.z));
  shapeMotionState = new btDefaultMotionState(startTransform);
  btRigidBody::btRigidBodyConstructionInfo rigid_body_information(mass,shapeMotionState,shape,localInertia);
  //rigid_body_information.m_restitution = cfg.restitution;
  rigid_body_information.m_friction = 0.5;
  body = new btRigidBody(rigid_body_information);
  std::cout << "Am I dynamic? " << std::boolalpha << cfg.is_dynamic << std::endl;
  
  if(cfg.is_dynamic)
  {
    //bool collision_flags = body->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT;
    //body->setCollisionFlags(collision_flags);
    body->setActivationState(DISABLE_DEACTIVATION);
  }
  if(cfg.is_kinematic)
  {
    //body is a btRigidBody pointer referencing the object being converted
    bool collision_flags = body->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT;
    body->setCollisionFlags(collision_flags);
  }
  
  

  dynamics_world->addRigidBody(body);

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
  delete body;
  delete shape;
  delete shapeMotionState;
}

//takes a character representing keyboard input and performs the
//proper mutations on the objects config
void Object::ProcessInput(char input)
{
  switch(input)
  {
    case 'w':
      //body->setActivationState(ACTIVE_TAG);
      body->applyCentralForce(btVector3(0,0,1000));
      //body->setActivationState(DISABLE_DEACTIVATION);
      std::cout << "w" << std::endl;
      break;
    case 'a':
      std::cout << "a" << std::endl;
      break;
    case 's':
      std::cout << "s" << std::endl;
      break;
    case 'd':
      std::cout << "d" << std::endl;
      break;
    default:
      break;
  }
}

void Object::Update(unsigned int dt, btDiscreteDynamicsWorld* dynamics_world)
{
  //body->activate(ACTIVE_TAG);
  dynamics_world->stepSimulation(dt/10000.f, 10);
  
  body->applyGravity();

  btTransform transform;
  body->getMotionState()->getWorldTransform(transform);

  btScalar m[16];
  transform.getOpenGLMatrix(m);

  model = glm::make_mat4(m);
  model *= glm::scale(glm::vec3(.1));
  //body->activate(DISABLE_DEACTIVATION);
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
    float scale = element->FloatText();
    cfg.scale = scale;
  }

  //set the object shape
  if((element = object->FirstChildElement("shape"))){
    char* shape = new char[256];
    strcpy(shape,element->GetText());
    cfg.shape = shape;
  }
  
  //set the is_dynamic flag
  if((element = object->FirstChildElement("dynamic"))){
    bool dynamic = element->BoolText();
    cfg.is_dynamic = dynamic;
  }
  
  //set the is_dynamic flag
  if((element = object->FirstChildElement("kinematic"))){
    bool kinematic = element->BoolText();
    cfg.is_kinematic = kinematic;
  }

  //set the mass
  if((element = object->FirstChildElement("mass"))){
    bool m = element->FloatText();
    cfg.mass = m;
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

  //length, width, height
  if((element = object->FirstChildElement("width"))){
    float m = element->FloatText();
    cfg.width = m;
  }
  if((element = object->FirstChildElement("length"))){
    float m = element->FloatText();
    cfg.length = m;
  }
  if((element = object->FirstChildElement("height"))){
    float m = element->FloatText();
    cfg.height = m;
  }

  //restitution
  if((element = object->FirstChildElement("restitution"))){
    float m = element->FloatText();
    cfg.restitution = m;
  }
  //friction
  if((element = object->FirstChildElement("friction"))){
    float m = element->FloatText();
    cfg.friction = m;
  }

  location = glm::vec3(x,y,z);
  model *= glm::translate(glm::mat4(1.0f),location); 
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
  SetTexture(texture);
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

void Object::SetTexture(GLuint text)
{
	texture = text;
}

void Object::LoadShape(char* shape_str){
  if((strcmp(shape_str,"mesh")) == 0){
    btTriangleMesh* triangle_mesh = new btTriangleMesh();
    for(unsigned int i = 0; i < Indices.size() - 2; i+=3){
      btVector3 v1(Vertices[i].vertex.x,Vertices[i].vertex.y,Vertices[i].vertex.z);
      btVector3 v2(Vertices[i+1].vertex.x,Vertices[i+1].vertex.y,Vertices[i+1].vertex.z);
      btVector3 v3(Vertices[i+2].vertex.x,Vertices[i+2].vertex.y,Vertices[i+2].vertex.z);
      triangle_mesh->addTriangle(v1,v2,v3);
    }
    if(!cfg.is_dynamic){
      shape = new btBvhTriangleMeshShape(triangle_mesh,true);
    }
    else{
      shape = new btConvexTriangleMeshShape(triangle_mesh,true);
    }
    shape->setLocalScaling(btVector3(cfg.scale,cfg.scale,cfg.scale));
  }
  else if((strcmp(shape_str,"sphere")) == 0){
    btScalar radius = cfg.scale;
    shape = new btSphereShape(radius*radius);
    std::cout << "Sphere type: " << shape->getShapeType() << std::endl;
  }
  else if((strcmp(shape_str,"box")) == 0){
    btVector3 vec = {cfg.width*cfg.scale, cfg.height*cfg.scale, cfg.length*cfg.scale};
    shape = new btBoxShape(vec);
    std::cout << "Box type: " << shape->getShapeType() << std::endl;
  }
  else if((strcmp(shape_str,"cylinder")) == 0){
    btVector3 vec = {cfg.width*cfg.scale, cfg.height*cfg.scale, cfg.length*cfg.scale};
    shape = new btCylinderShape(vec);
    std::cout << "Cylinder type: " << shape->getShapeType() << std::endl;
  }
  else if((strcmp(shape_str, "plane")) == 0){
    btVector3 vec = {cfg.width,cfg.height,cfg.length};
    btScalar plane_const = 0;
    shape = new btStaticPlaneShape(vec,plane_const);
  }
}

float Object::Scale(){
  return cfg.scale;
}

btRigidBody* Object::GetRigidBody(){
  return body;
}