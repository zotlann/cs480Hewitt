#ifndef FLIPPER_H
#define FLIPPER_H

#include "object.h"

class Flipper{
  public:
    Flipper(char* flipper_filename);
    void Flip();
    Object* GetFlipper();
    void Update(unsigned int dt);
  private:
    Object* flipper_object;
};

#endif //FLIPPER_H
