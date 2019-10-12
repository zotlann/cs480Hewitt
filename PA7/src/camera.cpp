#include "camera.h"

Camera::Camera()
{

}

Camera::~Camera()
{

}

bool Camera::Initialize(int w, int h)
{
  //--Init the view and projection matrices
  //  if you will be having a moving camera the view matrix will need to more dynamic
  //  ...Like you should update it before you render more dynamic 
  //  for this project having them static will be fine
  view = glm::lookAt( glm::vec3(0, 150, 90), //Eye Position. Default (0,50,8)
                      glm::vec3(0.0, 0.0, 0.0), //Focus point
                      glm::vec3(0.0, 1.0, 0.0)); //Positive Y is up

  projection = glm::perspective( 45.0f, //the FoV typically 90 degrees is good which is what this is set to
                                 float(w)/float(h), //Aspect Ratio, so Circles stay Circular
                                 0.01f, //Distance to the near plane, normally a small value like this
                                 500.0f); //Distance to the far plane, Default 100f
  return true;
}

void Camera::Input(char input)
{
  switch(input)
  {
    case 1:
    case 2:
    case 3:
      printf("nice\n");
      break;
    case 'w':
    case 'a':
    case 's':
    case 'd':
    case '^':
    case '<':
    case '>':
    case 'V':
    default:
      break;
  }
}

glm::mat4 Camera::GetProjection()
{	
  return projection;
}

glm::mat4 Camera::GetView()
{
  return view;
}


