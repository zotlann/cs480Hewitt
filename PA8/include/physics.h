#ifndef PHYSICS_H
#define PHYSICS_H

#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>
#include <vector>
#include "object.h"
class  PhysicsWorld{
	public:
		PhysicsWorld();
		~PhysicsWorld();

		void AddObject(Object*);
		void StepSimulation(unsigned int);

	private:
		btDiscreteDynamicsWorld* dynamics_world;
};

#endif
