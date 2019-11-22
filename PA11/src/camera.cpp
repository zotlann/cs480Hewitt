#include "camera.h"

Camera::Camera(){}
Camera::~Camera(){}

bool Camera::Initialize(int w, int h){
	//set camera location
	location.x = -30;
	location.y = 10;
	location.z = 0;
	//set the camera angle
	angle = 0;
	pitch = 0;
	//set camera direction
	direction.x = 0;
	direction.y = 0;
	direction.z = 0;
	//set camera orientation
	orientation = glm::vec3(0.0,cos(angle),sin(angle)); //Positive Y is up
	//set fov
	float fov = 45;
	//set aspect ratio
	float aspect_ratio = float(w)/float(h);
	//set distance to near plane, usually a very small value
	float near_plane = 0.01f;
	//est distance to far plane
	float far_plane = 2000.0f;
	view_matrix = glm::lookAt(location,direction,orientation);
	projection_matrix = glm::perspective(fov,aspect_ratio,near_plane,far_plane);
	
	return true;
}

void Camera::Update(unsigned int dt, char input, Object* player){
	float dt_float = (float)dt;
	glm::vec3 ballLocation = player->GetLocation();
	location = player->GetLocation();
	location.x += 10;
	location.y += 5;
	if(pitch > 0){
		pitch -= dt_float*M_PI/15000;
		if(pitch < 0){
			pitch = 0;
		}
	}
	if(pitch < 0){
		pitch += dt_float*M_PI/15000;
		if(pitch > 0){
			pitch = 0;
		}
	}
	if(angle > 0){
		angle -= dt_float*M_PI/15000;
		if(angle < 0){
			angle = 0;
		}
	}
	if(angle < 0){
		angle += dt_float*M_PI/15000;
		if(angle > 0){
			angle = 0;
		}
	}
	switch(input){
		case 's':
			pitch -= dt_float*M_PI/3000;
			if( pitch <= -M_PI/4 )
				pitch = -M_PI/4;
			break;
		case 'w':
			pitch += dt_float*M_PI/3000;
			if( pitch >= M_PI/4 )
				pitch = M_PI/4;
			break;
		case 'a':
			angle -= dt_float*M_PI/3000;
			if( angle <= -M_PI/4 )
				angle = -M_PI/4;
			break;
		case 'd':
			angle += dt_float*M_PI/3000;
			if( angle >= M_PI/4 )
				angle = M_PI/4;
			break;
		default:
			 break;
	}
	ballLocation.y += 5*sin(pitch);
	orientation = glm::vec3(sin(pitch),cos(angle),sin(angle));
	view_matrix = glm::lookAt(location,ballLocation,orientation);
}

glm::vec3 Camera::GetGravity(){
	float gx = -5*orientation.x;
	float gz = -5*orientation.z;
	return glm::vec3(gx,0,gz);
}

glm::mat4 Camera::GetProjectionMatrix(){
	return projection_matrix;
}

glm::mat4 Camera::GetViewMatrix(){
	return view_matrix;
}
