#include "physics.h"

PhysicsWorld::PhysicsWorld(){
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

  //set the gravity
  dynamics_world->setGravity(btVector3(0,-9.8,0));
}

PhysicsWorld::~PhysicsWorld(){
  delete dynamics_world;
  dynamics_world = NULL;
}

void PhysicsWorld::AddObject(Object* object){
  dynamics_world->addRigidBody(object->GetRigidBody());
}

void PhysicsWorld::StepSimulation(unsigned int dt){
  dynamics_world->stepSimulation(dt/1000,10);
}

btDiscreteDynamicsWorld* PhysicsWorld::GetWorld()
{
  return dynamics_world;
}