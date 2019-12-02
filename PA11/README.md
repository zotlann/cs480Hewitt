# PA11: Apesphere

## Team:
- [Benjamin Estela](https://github.com/nebunr)
- [Sidney Inouye](https://github.com/sinouye)
- [Jonathon Hewitt](https://github.com/zotlann)

## Project Description
Apesphere.

## Dependency Instructions
To run this project on Linux, installation of these three programs are required [GLEW](http://glew.sourceforge.net/), [GLM](http://glm.g-truc.net/0.9.7/index.html), and [SDL2](https://wiki.libsdl.org/Tutorials).

This project uses OpenGL 3.3. Some computers, such as virtual machines in the ECC, can not run this version. In in order to run OpenGL 2.7 follow the instructions at [Using OpenGL 2.7](https://github.com/HPC-Vis/computer-graphics/wiki/Using-OpenGL-2.7)

### Ubuntu/Linux
Assimp, Magick++, and Bullet are needed.
```bash
sudo apt-get install libglew-dev libglm-dev libsdl2-dev libassimp-dev libbullet-dev
```

## Build Instructions
NOTE: Building with cmake will cause the executable to be called ./Tutorial. Cmake is not officially supported, but it will build. Change the commands as necessary if built using cmake.

Use make with the following commands:
```bash
mkdir build
cp makefile build
cd build
make
```

## Usage Instructions
```bash
./apesphere -c [master_config_file]
```
**EXAMPLE:**
```bash
./apesphere -c ../assets/configs/apesphere/master.xml
```
NOTE: If collisions do not work, please restart the program.

## Keyboard
| Input | Output |
| - |:-:|
| <kbd>Esc</kbd> | Exit program|

## Extra Credit
N/A

## Manual
The current manual can be found [here](https://docs.google.com/document/d/1aIcbmTQSdgDmyJRhLJwzB5e0xmMzvdijlrm1QTCOtoU/edit?usp=sharing).