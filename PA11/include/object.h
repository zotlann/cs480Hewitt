#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <fstream>
#include <tinyxml2.h>
#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>

#include "graphics_headers.h"
#include "model.h"
#include "texture.h"

struct ObjectConfig{
	glm::vec3 position;
	float scale;
	float mass;
	float restitution;
	float friction;
	char* texture_filename;
	char* model_filename;
	char* shape;
	bool is_kinematic;
};

class Object{
	public:
		Object(char* object_config_filename);
		Object();
		~Object();
		void Update(unsigned int dt);
		void ProcessInput(char input);
		void Render();
		void LoadModel(char* model_filename);
		void LoadTexture(char* texture_filename);
		void LoadBody(char* shape_str);
		void LoadShape(char* shape_str);
		void LoadObjectConfig(char* object_config_filename);
		glm::mat4 GetModelMatrix();
		glm::vec3 GetLocation();
		btRigidBody* GetRigidBody();
	private:
		glm::mat4 model_matrix;
		glm::vec3 location;

		Model* model;
		Texture* texture;

		ObjectConfig config;

		btCollisionShape* shape;
		btRigidBody* body;
		btDefaultMotionState* motion_state;
		btTriangleMesh* triangle_mesh;
};

		

#endif //OBJECT_H
