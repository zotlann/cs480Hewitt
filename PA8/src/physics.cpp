#include "physics.h"

PhysicsWorld::PhysicsWorld(){
  //set up broadphase
  btBroadphaseInterface* broadphase = new btDbvtBroadphase();

  //set up collision configuration
  btDefaultCollisionConfiguration* collision_config = new btDefaultCollisionConfiguration();

  //set up dispatcher
  btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collision_config);

  //set up solver
  btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;


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
