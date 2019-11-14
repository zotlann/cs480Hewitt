#include "flipper.h"

Flipper::Flipper(char* flipper_filename){
  flipper_object = new Object(flipper_filename);
}

void Flipper::Flip(){
}

Object* Flipper::GetFlipper(){
  return flipper_object;
}
