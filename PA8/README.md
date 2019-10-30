# PA8: Bullet

## Team:
- [Benjamin Estela](https://github.com/nebunr)
- [Sidney Inouye](https://github.com/sinouye)
- [Jonathon Hewitt](https://github.com/zotlann)

## Project Description
This project, PA8, uses the Bullet Physics Library to have collision detection and proper movement in our objects. While collision should work on our objects (also with triangle meshes!), nothing moves as of the early morning of October 30th.

## Dependency Instructions
To run this project on Linux, installation of these three programs are required [GLEW](http://glew.sourceforge.net/), [GLM](http://glm.g-truc.net/0.9.7/index.html), and [SDL2](https://wiki.libsdl.org/Tutorials).

This project uses OpenGL 3.3. Some computers, such as virtual machines in the ECC, can not run this version. In in order to run OpenGL 2.7 follow the instructions at [Using OpenGL 2.7](https://github.com/HPC-Vis/computer-graphics/wiki/Using-OpenGL-2.7)

### Ubuntu/Linux
Assimp, Magick++, and Bullet are needed.
```bash
sudo apt-get install libglew-dev libglm-dev libsdl2-dev libassimp-dev libbullet-dev
```

## Build Instructions
NOTE: Building with cmake will cause the executable to be called ./Tutorial.  Cmake is not officially supported, but it will build. Change the commands as necessary if built using cmake.

Use make with the following commands:
```bash
mkdir build
cp makefile build
cd build
make
```

## Usage Instructions
```bash
./PA8 -c [master_config_file]
```
**EXAMPLE:**
```bash
./PA8 -c ../assets/configs/bullet_test/master.xml
```

## Keyboard
| Input | Output |
| - |:-:|
| <kbd>&#8592;</kbd> | N/A |
| <kbd>&#8593;</kbd> | N/A |
| <kbd>&#8594;</kbd> | N/A |
| <kbd>&#8595;</kbd> | N/A |
| <kbd>Tab</kbd> | N/A |
