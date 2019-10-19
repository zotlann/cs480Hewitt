# PA8: Bullet

## Team:
- [Benjamin Estela](https://github.com/nebunr)
- [Sidney Inouye](https://github.com/sinouye)
- [Jonathon Hewitt](https://github.com/zotlann)

## Project Description
Bullet.

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
./PA8 -c ../assets/configs/[folder]/master.xml
```

NOTE: After starting, would recommend resetting the view with middle mouse as mouse movement to set the window into focus can throw off the camera.

## Mouse
| Input | Output |
| - |:-:|
| Left Mouse | Move up |
| Right Mouse | Move down |
| Middle Mouse | Reset camera |
| Move Mouse | Look around |

## Keyboard
| Input | Output |
| - |:-:|
| <kbd>&#8592;</kbd> | Move left |
| <kbd>&#8593;</kbd> | Move forward |
| <kbd>&#8594;</kbd> | Move right |
| <kbd>&#8595;</kbd> | Move back |
| <kbd>Tab</kbd> | Cycle through objects (terminal prints selected object) |