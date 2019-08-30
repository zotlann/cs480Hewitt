#include <iostream>

#include "engine.h"

/*
 * Parses the command line arguments. If the command line arguments are 
 * invalid or -h, display the correct format for the command line arguments.
 * set shaders[0] to the filename following -v for the vertex shader
 * set shaders[1] to the filename following -f for the fragment shader
 */

bool parseCmdArgs(int argc, char **argv, char** shaders){
  if((argc <= 2) || (strcmp(argv[1],"-h")==0)){
    printf("%s -v [vertex_shaders] -f [fragment_shaders]\n",argv[0]);
    return false;
  }
  else if(strcmp(argv[1],"-f") && strcmp(argv[3],"-v")){
    shaders[0] = argv[2];
    shaders[1] = argv[4];
    return true;
  }
  else if(strcmp(argv[1],"-v") && strcmp(argv[3],"-f")){
    shaders[0] = argv[4];
    shaders[1] = argv[2];
    return true;
  }
  else{
    printf("%s -v [vertex_shaders =f [fragment_shaders]\n",argv[0]);
  }
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
