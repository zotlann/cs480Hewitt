# PA7: Solar System
## Team:
Benjamin Estela
Jonathon Hewitt
Sidney Inouye

## Project Description
This project implements a model loader using the Assimp importer library. This allows this project, and further projects, to load a variety of object files.
## Build Instructions

NOTE: Building with cmake will cause the executable to be called ./Tutorial.  Cmake is not officially supported, but it will build. Change the commands as necessary if built using cmake.

```bash
mkdir build
cp makefile build
cd build
make
```

## Usage Instructions
```bash
./PA5 -v [vector_shader] -f [fragment_shader] -c [master_config_file]
```
EXAMPLE:
```
./PA5 -v ../assets/shaders/vshader -f ../assets/shaders/fshader -c ../assets/configs/sun.xml
```
