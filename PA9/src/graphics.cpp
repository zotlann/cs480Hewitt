#include "graphics.h"

Graphics::Graphics()
{

}

Graphics::~Graphics()
{
  delete dynamics_world;
  delete broadphase;
  delete collision_config;
  delete dispatcher;
  delete solver;  
}

bool Graphics::Initialize(int width, int height, Config cfg)
{
  // Used for the linux OS
  #if !defined(__APPLE__) && !defined(MACOSX)
    // cout << glewGetString(GLEW_VERSION) << endl;
    glewExperimental = GL_TRUE;

    auto status = glewInit();

    // This is here to grab the error that comes from glew init.
    // This error is an GL_INVALID_ENUM that has no effects on the performance
    glGetError();


    //Check for error
    if (status != GLEW_OK)
    {
      std::cerr << "GLEW Error: " << glewGetErrorString(status) << "\n";
      return false;
    }
  #endif
  // For OpenGL 3
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  // Init Camera
  m_camera = new Camera();
  if(!m_camera->Initialize(width, height))
  {
    printf("Camera Failed to Initialize\n");
    return false;
  }

  //Create the physics world
  //set up broadphase
  broadphase = new btDbvtBroadphase();

  //set up collision configuration
  collision_config = new btDefaultCollisionConfiguration();

  //set up dispatcher
  dispatcher = new btCollisionDispatcher(collision_config);

  //set up solver
  solver = new btSequentialImpulseConstraintSolver;

  //set up the world
  dynamics_world = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collision_config );

  //set gravity
  dynamics_world->setGravity(btVector3(0,-10,0));

  //Create the objects
  m_ball =  new Object(cfg.ball_config, dynamics_world);
  m_cube = new Object(cfg.cube_config, dynamics_world);
  m_cylinder = new Object(cfg.cylinder_config, dynamics_world);
  m_table = new Object(cfg.table_config, dynamics_world);

  //set up the objects vector
  objects.clear();
  objects.push_back(m_ball);
  objects.push_back(m_cube);
  objects.push_back(m_cylinder);
  objects.push_back(m_table);

  // Set up the shaders'
  Shader* s1 = new Shader();
  Shader* s2 = new Shader();

  if(!s1->Initialize())
  {
    printf("Shader Failed to Initialize\n");
    return false;
  }
  // Add the vertex shader
  if(!s1->AddShader(GL_VERTEX_SHADER,cfg.vshader1_filename))
  {
    printf("Vertex Shader failed to Initialize\n");
    return false;
  }

  // Add the fragment shader
  if(!s1->AddShader(GL_FRAGMENT_SHADER,cfg.fshader1_filename))
  {
    printf("Fragment Shader failed to Initialize\n");
    return false;
  }
  // Connect the program
  if(!s1->Finalize())
  {
    printf("Program to Finalize\n");
    return false;
  }

  //push the program to the shaders vertex
  m_shaders.push_back(s1);
  
  if(!s2->Initialize())
  {
    printf("Shader Failed to Initialize\n");
    return false;
  }
  // Add the vertex shader
  if(!s2->AddShader(GL_VERTEX_SHADER,cfg.vshader2_filename))
  {
    printf("Vertex Shader failed to Initialize\n");
    return false;
  }

  // Add the fragment shader
  if(!s2->AddShader(GL_FRAGMENT_SHADER,cfg.fshader2_filename))
  {
    printf("Fragment Shader failed to Initialize\n");
    return false;
  }
  // Connect the program
  if(!s2->Finalize())
  {
    printf("Program to Finalize\n");
    return false;
  }

  m_shaders.push_back(s2);
  
  shader_index = 0;


  // Locate the projection matrix in the shader
  m_projectionMatrix = m_shaders[shader_index]->GetUniformLocation("projectionMatrix");
  if (m_projectionMatrix == INVALID_UNIFORM_LOCATION) 
  {
    printf("m_projectionMatrix not found\n");
    return false;
  }

  // Locate the view matrix in the shader
  m_viewMatrix = m_shaders[shader_index]->GetUniformLocation("viewMatrix");
  if (m_viewMatrix == INVALID_UNIFORM_LOCATION) 
  {
    printf("m_viewMatrix not found\n");
    return false;
  }

  // Locate the model matrix in the shader
  m_modelViewMatrix = m_shaders[shader_index]->GetUniformLocation("modelViewMatrix");
  m_lightPosition = m_shaders[shader_index]->GetUniformLocation("lightPosition");
  m_shininess = m_shaders[shader_index]->GetUniformLocation("shininess");
  m_ambient = m_shaders[shader_index]->GetUniformLocation("AmbientProduct");
  m_diffuse = m_shaders[shader_index]->GetUniformLocation("DiffuseProduct");
  m_specular = m_shaders[shader_index]->GetUniformLocation("SpecularProduct");

  if (m_modelMatrix == INVALID_UNIFORM_LOCATION) 
  {
    printf("m_modelMatrix not found\n");
    return false;
  }

  //Locate lighting uniforms in the shader
  m_modelMatrix = m_shaders[shader_index]->GetUniformLocation("modelViewMatrix");
  //enable depth testing
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  return true;
}

void Graphics::Update(unsigned int dt,char input,glm::vec2 mouseLocation)
{
  if(input == '\t'){
    shader_index++;
    shader_index %= m_shaders.size();
    std::cout << shader_index << std::endl;
  }
  //set the timestep
  //update the ball with user input
  m_ball->ProcessInput(input);
  //update all the objects
  for(unsigned int i = 0; i < objects.size(); i++){
    objects[i]->Update(dt, dynamics_world);
  }
}

void Graphics::Render()
{
  //clear the screen and sets the black background
  glClearColor(0.0, 0.0, 1.0, 1.0); //Default: (0.0, 0.0, 0.2, 1.0)
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // Start the correct program
  m_shaders[shader_index]->Enable();

  // Send in the projection and view to the shader
  glUniformMatrix4fv(m_projectionMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetProjection())); 
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetView())); 

  // Render the objects
  for(unsigned int i = 0; i < objects.size(); i++)
  {
    glm::mat4 modelView = m_camera->GetView() * objects[i]->GetModel();
    //glm::mat4 modelView = objects[i]->GetModel() * m_camera->GetView();
    glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(objects[i]->GetModel()));
    glUniformMatrix4fv(m_modelViewMatrix, 1, GL_FALSE, glm::value_ptr(modelView));
    glUniform3fv(m_lightPosition, 1, glm::value_ptr(glm::vec3(1.0,1.0,1.0)));
    glUniform1f(m_shininess, 1.0f);
    glUniform4fv(m_ambient, 1, glm::value_ptr(glm::vec4(1.0f,20.0f,1.0f,1.0f)));
    glUniform4fv(m_diffuse, 1, glm::value_ptr(glm::vec4(1.0f)));
    glUniform4fv(m_specular, 1, glm::value_ptr(glm::vec4(1.0f)));

    objects[i]->Render();
  }

  // Get any errors from OpenGL
  auto error = glGetError();
  if ( error != GL_NO_ERROR )
  {
    string val = ErrorString( error );
  }
}

std::string Graphics::ErrorString(GLenum error)
{
  if(error == GL_INVALID_ENUM)
  {
    return "GL_INVALID_ENUM: An unacceptable value is specified for an enumerated argument.";
  }

  else if(error == GL_INVALID_VALUE)
  {
    return "GL_INVALID_VALUE: A numeric argument is out of range.";
  }

  else if(error == GL_INVALID_OPERATION)
  {
    return "GL_INVALID_OPERATION: The specified operation is not allowed in the current state.";
  }

  else if(error == GL_INVALID_FRAMEBUFFER_OPERATION)
  {
    return "GL_INVALID_FRAMEBUFFER_OPERATION: The framebuffer object is not complete.";
  }

  else if(error == GL_OUT_OF_MEMORY)
  {
    return "GL_OUT_OF_MEMORY: There is not enough memory left to execute the command.";
  }
  else
  {
    return "None";
  }
}

