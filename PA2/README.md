# PA2: Interactions: Menus, Keyboard, and Mouse

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
./PA2 -v [vector_shader] -f [fragment_shader] -c [planet_config]
```

The -v, -f, and -c command line arguments can be used in any order, use the -h command line argument to display the proper format for running the program.

[vector_shader] and [fragment_shader] are paths to the vector and fragment shader files respectively. By default these are in ../assets/shaders/vshader and ../assets/shaders/fshader respectively.

[planet_config] is a config file with planet data. If no planet config is given default values will be used.  There is an example planet.conf in ../assets/entities/planet.conf.  Feel free to alter data in this config file to change the intial movement patterns of the planet.

To run the program with it's default shaders and standard settings run
```bash
./PA2 -v ../assets/shaders/vshader -f ../assets/shaders/fshader
```
or
```bash
./PA2 -f ../assets/shaders/fshader -v ../assets/shaders/vshader
```

To add in the planet config try
```bash
./PA2 -v ../assets/shaders/vshader -f ../assets/shaders/fshader -c ../assets/entities/planet.conf
```

NOTE: When using a planet config file, the parseConfig command currently falsely reports an error in formatting on a null string.  This error should be ignored for now.  Any other errors from improperly formatted configs or unexpected tokens should be properly reported, but no extensive testing has been done on the parser as of now.

## User Interaction
This version of the program takes user input and alters the motion of the cube based on the input.

## KEYBINDS

### Mouse:
Left Mouse Button: Change the direction the cube rotates about it's y axis.  
Right Mouse Button: Change the direction the cube orbits about the center of the window.  

### Keyboard:
Q: Change the direction the cube rotates about it's y axis.  
W: Decrease the speed of rotation when moving counter-clockwise.
E: Increase the speed of rotaion when moving couner-clockwise.
R: Toggle pause/resume rotation.  
A: Change the direction the cube orbits around the center.  
S: Decrease the speed of orbit when moving counter-clockwise.  
D: Increase the speed of orbit when moving counter-clockwise.
F: Toggle pause/resume orbit.  
Z: Decrease the radius of the orbit.  
X: Increase the radius of the orbit.  
C: Decrease the size of the cube.  
V: Increase the size of the cube.  
