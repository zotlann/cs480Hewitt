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
	//location = player->GetLocation();
	//location.x += 10;
	if(direction.y < 0){
		direction.y += dt_float/1000;
		if(direction.y > 0){
			direction.y = 0;
		}
	}
	if(direction.y > 0){
		direction.y -= dt_float/1000;
		if(direction.y < 0){
			direction.y = 0;
		}
	}
	if(angle > 0){
		angle -= dt_float*M_PI/50000;
		if(angle < 0){
			angle = 0;
		}
	}
	if(angle < 0){
		angle += dt_float*M_PI/50000;
		if(angle > 0){
			angle = 0;
		}
	}
	switch(input){
		case 'w':
			direction.x += (float)dt_float/100.0;
			break;
		case 's':
			direction.x -= (float)dt_float/100.0;
			break;
		case 'a':
			angle -= dt_float*M_PI/5000;
			break;
		case 'd':
			angle += dt_float*M_PI/5000;
			break;
		default:
			 break;
	}
	orientation = glm::vec3(0.0,cos(angle),sin(angle));
	view_matrix = glm::lookAt(location,direction,orientation);

}

glm::vec3 Camera::GetGravity(){
	float gx = direction.x;
	float gz = -5*orientation.z;
	return glm::vec3(gx,0,gz);
}

glm::mat4 Camera::GetProjectionMatrix(){
	return projection_matrix;
}

glm::mat4 Camera::GetViewMatrix(){
	return view_matrix;
}
