#include "flipper.h"

Flipper::Flipper(char* flipper_filename){
  flipper_object = new Object(flipper_filename);
}

void Flipper::Flip(){
  btRigidBody* bd = flipper_object->GetRigidBody();
  btTransform tr;
  tr.setIdentity();
  btQuaternion quat;
  quat.setEulerZYX(0,1,0);
  tr.setRotation(quat);
  bd->setCenterOfMassTransform(tr);
  btScalar x,y,z;
}

void Flipper::Update(unsigned int dt){
  btTransform tr;
  btRigidBody* bd = flipper_object->GetRigidBody();
  tr.setIdentity();
  btQuaternion quat;
  btScalar x,y,z;
  flipper_object->GetRigidBody()->getWorldTransform().getBasis().getEulerZYX(z,y,x);
  flipper_object->GetRigidBody()->getMotionState()->getWorldTransform(tr);
  //std::cout << z << " " << y << " " << x << std::endl;
  if( y > 0.0f ){
    std::cout << "TEST" << std::endl;
    y -= 0.5;
    if(y < 0.0f){
      y = 0;
    }
    std::cout << z << " " << y << " " << x << std::endl;
  }
  quat.setEulerZYX(0,y,0);
  tr.setRotation(quat);
  bd->setCenterOfMassTransform(tr);
  bd->getWorldTransform().getBasis().getEulerZYX(z,y,x);
  //std::cout << "A: " << y << std::endl;
}
Object* Flipper::GetFlipper(){
  return flipper_object;
}
