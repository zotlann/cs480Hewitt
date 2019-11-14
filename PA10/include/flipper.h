#ifndef FLIPPER_H
#define FLIPPER_H

#include "object.h"

class Flipper{
  public:
    Flipper(char* flipper_filename);
    void Flip();
    Object* GetFlipper();
  private:
    Object* flipper_object;
};

#endif //FLIPPER_H
