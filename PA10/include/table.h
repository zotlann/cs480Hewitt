#ifndef TABLE_H
#define TABLE_H

#include "object.h"
#include "flipper.h"

class Table{
  public:
    Table(char* table_filename);
    void FlipLeftFlippers();
    void FlipRightFlippers();
    glm::vec3 GetStartingBallPosition();
    Object* GetBall();
    std::vector<Object*> GetObjects();
  private:
    std::vector<Flipper*> left_flippers;
    std::vector<Flipper*> right_flippers;
    std::vector<Object*> objects;
    Object* table;
    Object* ball;
    glm::vec3 starting_ball_position;
};

#endif //TABLE_H
