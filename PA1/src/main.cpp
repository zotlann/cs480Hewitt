#include <iostream>

#include "engine.h"

/*
 * Parses the command line arguments. If the command line arguments are 
 * invalid or -h, display the correct format for the command line arguments.
 * set shaders[0] to the filename following -v for the vertex shader
 * set shaders[1] to the filename following -f for the fragment shader
 */

bool parseCmdArgs(int argc, char **argv, char** shaders){
  char help_message[256];
  sprintf(help_message,"%s -v [vertex_shader] -f [fragment_shader]\n",argv[0]);
  if(argc < 2){
    printf("%s",help_message);
    return false;
  }
  for(int i = 1; i < argc; i++){
    if((strcmp(argv[i],"-h")==0)){
      printf("%s",help_message);
      return false;
    }
    if((strcmp(argv[i],"-v")==0)){
      shaders[0] = argv[i+1];
    }
    else if((strcmp(argv[i],"-f")==0)){
      shaders[1] = argv[i+1];
    }
  }
  return true;
}
 


int main(int argc, char **argv)
{
  char* shaders[2];

  if(!parseCmdArgs(argc,argv,shaders)){
    return 0;
  }

  // Start an engine and run it then cleanup after
  Engine *engine = new Engine("Tutorial Window Name", 800, 600);
  if(!engine->Initialize(shaders))
  {
    printf("The engine failed to start.\n");
    delete engine;
    engine = NULL;
    return 1;
  }
  engine->Run();
  delete engine;
  engine = NULL;
  return 0;
}
