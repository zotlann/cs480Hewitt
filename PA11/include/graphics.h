#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <iostream>

#include "graphics_headers.h"
#include "camera.h"
#include "shader.h"
#include "object.h"
#include "physics.h"

class Graphics{
	public:
		Graphics();
		~Graphics();
		bool Initialize(int w, int h, Config cfg);
		void Update(unsigned int dt, char input);
		void Render();
		void Input(char input);
		char* ErrorString(GLenum error);
	private:

		Camera* camera;
		std::vector<Shader*> shaders;

		GLint projection_matrix;
		GLint view_matrix;
		GLint model_matrix;
		GLint model_view_matrix;

		PhysicsWorld* physics_world;

		std::vector<Object*> objects;
};

#endif //GRAPHICS_H
