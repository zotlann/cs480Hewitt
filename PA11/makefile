# Check for OS Type
UNAME_S := $(shell uname -s)

# Linux
ifeq ($(UNAME_S), Linux)
	CC=g++
	LIBS=-lSDL2 -lGLEW -lGL -lassimp `Magick++-config --cppflags --cxxflags --ldflags --libs` -lBulletDynamics -lBulletSoftBody -lBulletCollision -lLinearMath
# Mac
else
	CC=clang++
	LIBS=-lSDL2 -framework OpenGL -framework Cocoa -lGLEW -stdlib=libc++ -lassimp
endif

#Compiler Flags
CXXFLAGS=-g -Wall -std=c++0x `Magick++-config --cppflags --cxxflags --ldflags --libs`

# .o Compilation
O_FILES=main.o camera.o engine.o graphics.o object.o shader.o window.o tinyxml2.o model.o texture.o physics.o keyhandler.o

# Point to includes of local directories
INCLUDES=-I../include -I/usr/include/bullet

all: $(O_FILES)
	$(CC) $(CXXFLAGS) -o PA10 $(O_FILES) $(LIBS) #$(PATHI) $(PATHL)

main.o: ../src/main.cpp
	$(CC) $(CXXFLAGS) -c ../src/main.cpp -o main.o $(INCLUDES)

camera.o: ../src/camera.cpp
	$(CC) $(CXXFLAGS) -c ../src/camera.cpp -o camera.o $(INCLUDES)

engine.o: ../src/engine.cpp
	$(CC) $(CXXFLAGS) -c ../src/engine.cpp -o engine.o $(INCLUDES)

graphics.o: ../src/graphics.cpp
	$(CC) $(CXXFLAGS) -c ../src/graphics.cpp -o graphics.o $(INCLUDES)

object.o: ../src/object.cpp
	$(CC) $(CXXFLAGS) -c ../src/object.cpp -o object.o $(INCLUDES)

shader.o: ../src/shader.cpp
	$(CC) $(CXXFLAGS) -c ../src/shader.cpp -o shader.o $(INCLUDES)

window.o: ../src/window.cpp
	$(CC) $(CXXFLAGS) -c ../src/window.cpp -o window.o $(INCLUDES)

tinyxml2.o: ../src/tinyxml2.cpp
	$(CC) $(CXXFLAGS) -c ../src/tinyxml2.cpp -o tinyxml2.o $(INCLUDES)
model.o: ../src/model.cpp
	$(CC) $(CXXFLAGS) -c ../src/model.cpp -o model.o $(INCLUDES)
texture.o: ../src/texture.cpp
	$(CC) $(CXXFLAGS) -c ../src/texture.cpp -o texture.o $(INCLUDES)
physics.o: ../src/physics.cpp
	$(CC) $(CXXFLAGS) -c ../src/physics.cpp -o physics.o $(INCLUDES)
keyhandler.o: ../src/keyhandler.cpp
	$(CC) $(CXXFLAGS) -c ../src/keyhandler.cpp -o keyhandler.o $(INCLUDES)

clean:
	-@if rm *.o PA10 2>/dev/null || true; then echo "Main Removed"; else echo "No Main"; fi
