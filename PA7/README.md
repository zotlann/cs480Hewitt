# PA7: Solar System

## Team:
- [Benjamin Estela](https://github.com/nebunr)
- [Sidney Inouye](https://github.com/sinouye)
- [Jonathon Hewitt](https://github.com/zotlann)

## Project Description
It's the solar system.

## Dependency Instructions
To run this project on Linux, installation of these three programs are required [GLEW](http://glew.sourceforge.net/), [GLM](http://glm.g-truc.net/0.9.7/index.html), and [SDL2](https://wiki.libsdl.org/Tutorials).

This project uses OpenGL 3.3. Some computers, such as virtual machines in the ECC, can not run this version. In in order to run OpenGL 2.7 follow the instructions at [Using OpenGL 2.7](https://github.com/HPC-Vis/computer-graphics/wiki/Using-OpenGL-2.7)

### Ubuntu/Linux
Assimp and Magick++ are needed. Also fun fact, the makefile we use will be different than the one pushed for grading.
```bash
sudo apt-get install libglew-dev libglm-dev libsdl2-dev libassimp-dev
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
./PA7 -v [vector_shader] -f [fragment_shader] -c [master_config_file]
```
**EXAMPLE:**
```bash
./PA7 -v ../assets/shaders/vshader -f ../assets/shaders/fshader -c ../assets/configs/[folder]/master.xml
```
*OR*
```bash
./PA7 -c ../assets/configs/small_sun/master.xml
```

## Mouse
| Input | Output |
| - |:-:|
| Left Mouse | . |
| Right Mouse | . |
| Middle Mouse | . |

## Keyboard
| Input | Output |
| - |:-:|
| <kbd>Q</kbd> | . |
| <kbd>W</kbd> | . |
| <kbd>A</kbd> | . |
| <kbd>S</kbd> | . |
| <kbd>D</kbd> | . |
| <kbd>F</kbd> | . |
| <kbd>R</kbd> | . |
| <kbd>&#8592;</kbd> | . |
| <kbd>&#8593;</kbd> | . |
| <kbd>&#8594;</kbd> | . |
| <kbd>&#8595;</kbd> | . |
| <kbd>`</kbd> | . |
| <kbd>1</kbd> | . |
| <kbd>2</kbd> | . |
| <kbd>3</kbd> | . |
| <kbd>4</kbd> | . |
| <kbd>5</kbd> | . |
| <kbd>6</kbd> | . |
| <kbd>7</kbd> | . |
| <kbd>8</kbd> | . |
| <kbd>9</kbd> | . |
| <kbd>0</kbd> | . |

## Extra Credit
Live adjustment of simulation speed? **Of course.**  
Configuration file? **Ever heard of .xml? We got plenty of those.**  

Draws planet orbit path?  
Option to go from actual data to scaled view?   
Proper rings on other planets?  

*Flat Earth though...* Let me show you this: `--flat `  