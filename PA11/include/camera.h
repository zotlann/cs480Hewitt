#ifndef CAMERA_H
#define CAMERA_H

#include "graphics_headers.h"
#include "object.h"
class Camera{
	public:
		Camera();
		~Camera();
		bool Initialize(int w, int h);
		void Update(unsigned int dt,char input, Object* player);
		glm::mat4 GetProjectionMatrix();
		glm::mat4 GetViewMatrix();
		glm::vec3 GetGravity();
	private:
		glm::mat4 projection_matrix;
		glm::mat4 view_matrix;
		glm::vec3 location;
		glm::vec3 direction;
		glm::vec3 orientation;
		float angle;
};

#endif //CAMERA_H
