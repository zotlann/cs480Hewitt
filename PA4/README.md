# PA3: Moons

## Project Description
This project added another object to render in a moon that orbits the original cube.  Both objects are controlled independantly similarly to the capabilities in PA2.  

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
./PA3 -v [vector_shader] -f [fragment_shader]
```

The -v and -f command line arguments can be used in any order, use the -h command line argument to display the proper format for running the program.

[vector_shader] and [fragment_shader] are paths to the vector and fragment shader files respectively. By default these are in ../assets/shaders/vshader and ../assets/shaders/fshader respectively.

To run the program with it's default shaders and standard settings run
```bash
./PA3 -v ../assets/shaders/vshader -f ../assets/shaders/fshader
```
or
```bash
./PA3 -f ../assets/shaders/fshader -v ../assets/shaders/vshader
```

## User Interaction
This version of the program takes user input and alters the motion of the cube based on the input.

## KEYBINDS

### Mouse:
Left Mouse Button: Change the direction the cube rotates about it's y axis.  
Right Mouse Button: Change the direction the cube orbits about the center of the window.  

### Keyboard:
TAB: Change the entity that is targeted and therefore effected by input.  
e.g if the planet is selected and you hit tab the moon will become selected and any subsequent inputs will alter the moon's motion and vice versa.  
The program starts with the planet selected.  
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

### EXTRA CREDIT:
Scaled Moon:  
The moon starts off with a scalar of 0.5 it's original size.  You can alter this at runtime by hitting tab, to target the moon, and then c or v to decrease or increase the size of it respectively.

Adjust Moon Speed:  
The moon starts off at the same relative speed as the planet.  You can alter this at runtime by hitting tab, to target the moon, and then w or e to decrease or increase the speed of the rotation respectively, and s or d to decrease or increase the speed of the orbit respectively.  Any other binds shown above work properly as well when targeted on the moon.
