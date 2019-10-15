#include "camera.h"

Camera::Camera()
{

}

Camera::~Camera()
{

}

bool Camera::Initialize(int w, int h)
{
  // Init cameraLocation for update
  cameraLocation_x = 180;
  cameraLocation_y = 0;
  cameraLocation_z = 0;
  xLook = 0;
  yLook = 0;
  zLook = 0;

  //--Init the view and projection matrices
  //  if you will be having a moving camera the view matrix will need to more dynamic
  //  ...Like you should update it before you render more dynamic 
  //  for this project having them static will be fine
  view = glm::lookAt( glm::vec3(180, 0, 0), //Eye Position. Default (0,50,8)
                      glm::vec3(0.0, 0.0, 0.0), //Focus point
                      glm::vec3(0.0, 1.0, 0.0)); //Positive Y is up

  projection = glm::perspective( 45.0f, //the FoV typically 90 degrees is good which is what this is set to
                                 float(w)/float(h), //Aspect Ratio, so Circles stay Circular
                                 0.01f, //Distance to the near plane, normally a small value like this
                                 2000.0f); //Distance to the far plane, Default 100f
  return true;
}

void Camera::Update(unsigned int dt, glm::vec2 mouseLocation)
{
  //cameraLocation_x += mouseLocation.x;
  //cameraLocation_y += mouseLocation.y;
  //mouseLocation.x *= dt;
  view = glm::lookAt( glm::vec3(cameraLocation_x, cameraLocation_y, cameraLocation_z),
                      glm::vec3(xLook, yLook, zLook),
                      glm::vec3(0.0, 1.0, 0.0));
}

void Camera::Input(char input)
{
  int movement = 10;
  switch(input)
  {
    case 1:
      //printf("left\n");
      cameraLocation_y += movement;
      yLook += movement;
      break;
    case 2:
      //printf("right\n");
      cameraLocation_y -= movement;
      yLook -= movement;
      break;
    case 3:
      //printf("middle\n");
      break;
    case '^':
      cameraLocation_x -= movement;
      xLook -= movement;
      break;
    case '<':
      cameraLocation_z += movement;
      zLook += movement;
      break;
    case '>':
      cameraLocation_z -= movement;
      zLook -= movement;
      break;
    case 'V':
      cameraLocation_x += movement;
      xLook += movement;
      break;
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


