#include "graphics.h"

Graphics::Graphics(){}
Graphics::~Graphics(){}

bool Graphics::Initialize(int w, int h, Config cfg){
	//used for linux OS
	#if !defined(__APPLE__) && !defined(MACOSX)
		glewExperimental = GL_TRUE;
		auto status = glewInit();
		glGetError();
		if(status != GLEW_OK){
			std::cerr << "GLEW Error: " << glewGetErrorString(status) << "\n";
			return false;
		}
	#endif
	//For OpenGL 3
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//Init Camera
	camera = new Camera();
	if(!camera->Initialize(w,h)){
		printf("Camera Failed to Initialize\n");
		return false;
	}

	//Set up the shaders
	Shader* s1 = new Shader();
	if(!s1->Initialize()){
		printf("Shader Failed to Initialize\n");
		return false;
	}
	//Add the vertex shader
	if(!s1->AddShader(GL_VERTEX_SHADER,cfg.vshader_filename)){
		printf("Vertex Shader Failed to Initialize\n");
	}
	//Add the fragment shader
	if(!s1->AddShader(GL_FRAGMENT_SHADER,cfg.fshader_filename)){
		printf("Fragment Shader failed to Initialize\n");
	}
	//Connect the program
	if(!s1->Finalize()){
		printf("Program failed to Finalize\n");
		return false;
	}
	shaders.push_back(s1);

	//Locate the MVP matricies in the shader
	projection_matrix = shaders[0]->GetUniformLocation("projectionMatrix");
	if(projection_matrix == INVALID_UNIFORM_LOCATION){
		printf("projectionMatrix not found\n");
	}
	view_matrix = shaders[0]->GetUniformLocation("viewMatrix");
	if(view_matrix == INVALID_UNIFORM_LOCATION){
		printf("viewMatrix not found\n");
	}
	model_matrix = shaders[0]->GetUniformLocation("modelMatrix");
	if(model_matrix == INVALID_UNIFORM_LOCATION){
		printf("modelMatrix not found\n");
	}
	model_view_matrix = shaders[0]->GetUniformLocation("modelViewMatrix");
	if(model_view_matrix == INVALID_UNIFORM_LOCATION){
		printf("modelViewMatrix not found\n");
	}

	//set up the physics world
	physics_world = new PhysicsWorld(btVector3(10,-10,0));

	//set up the objects
	Object* object = new Object("../assets/configs/apesphere/table.xml");
	Object* object2 = new Object("../assets/configs/apesphere/ball.xml");
	objects.push_back(object);
	objects.push_back(object2);

	//add the objects to the physics world
	for(unsigned int i = 0; i < objects.size(); i++){
		physics_world->AddBody(objects[i]->GetRigidBody());
	}

	//enable depth testing
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	return true;
}

void Graphics::Update(unsigned int dt, KeyHandler* key_handler){
	camera->Update(dt,key_handler,objects[1]);
	glm::vec3 g = camera->GetGravity();
	g *= 5;
	physics_world->SetGravity(btVector3(g.x,g.y,g.z));

	physics_world->StepSimulation(dt);
	for(unsigned int i = 0; i < objects.size(); i++){
		objects[i]->Update(dt);
	}

	// friction simulation
	btScalar linearVelocity_x = objects[1]->GetRigidBody()->getLinearVelocity().getX();
	btScalar linearVelocity_y = objects[1]->GetRigidBody()->getLinearVelocity().getY();
	btScalar linearVelocity_z = objects[1]->GetRigidBody()->getLinearVelocity().getZ();
	if( linearVelocity_x > 0 )
	{
		linearVelocity_x -= float(dt)/5000.f;
		if( linearVelocity_x <= 0 )
			linearVelocity_x = 0;
	}
	if( linearVelocity_x < 0 )
	{
		linearVelocity_x += float(dt)/5000.f;
		if( linearVelocity_x >= 0 )
			linearVelocity_x = 0;
	}
		if( linearVelocity_z > 0 )
	{
		linearVelocity_z -= float(dt)/5000.f;
		if( linearVelocity_z <= 0 )
			linearVelocity_z = 0;
	}
	if( linearVelocity_z < 0 )
	{
		linearVelocity_z += float(dt)/5000.f;
		if( linearVelocity_z >= 0 )
			linearVelocity_z = 0;
	}

	objects[1]->GetRigidBody()->setLinearVelocity(btVector3(linearVelocity_x, linearVelocity_y, linearVelocity_z));
}

void Graphics::Render(){
	//clear the screen and set the black background
	glClearColor(0.0,0.0,0.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//start the shader
	shaders[0]->Enable();

	//send in the view and projection matrices to the shader
	glUniformMatrix4fv(projection_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetProjectionMatrix()));
	glUniformMatrix4fv(view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));

	//Render the objects
	for(unsigned int i = 0; i < objects.size(); i++){
		glm::mat4 model_view = camera->GetViewMatrix() * objects[i]->GetModelMatrix();
		glUniformMatrix4fv(model_matrix, 1, GL_FALSE, glm::value_ptr(objects[i]->GetModelMatrix()));
		glUniformMatrix4fv(model_view_matrix, 1, GL_FALSE, glm::value_ptr(model_view));
		objects[i]->Render();
	}

	//Get any errors from OpenGL
	auto error = glGetError();
	if(error != GL_NO_ERROR){
		printf("%s",ErrorString(error));
	}
}

char* Graphics::ErrorString(GLenum error){
	char ret[6];
	strcpy(ret,"test");
}
		