# PA1: Spinning Cube

## Build Instructions

```bash
mkdir build
cp makefile build
cd build
make
```

## Usage Instructions
```bash
./PA1 -v [vector_shader] -f [fragment_shader]
```

The -v and -f command line arguments can be used in any order, use the -h command line argument to display the proper format for running the program.

[vector_shader] and [fragment_shader] are paths to the vector and fragment shader files respectively. By default these are in ../shaders/vshader and ../shaders/fshader respectively.

To run the program with it's default shaders and standard settings run
```bash
./PA1 -v ../shaders/vshader -f ../shaders/fshader
```
or
```bash
./PA1 -f ../shaders/fshader -v ../shaders/vshader
```
