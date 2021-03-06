# Check for OS Type
UNAME_S := $(shell uname -s)

# Linux
ifeq ($(UNAME_S), Linux)
	CC=g++
	LIBS=-lSDL2 -lGLEW -lGL -lassimp -lBulletDynamics -lBulletSoftBody -lBulletCollision -lLinearMath -lMagick++-6.Q16 #`Magick++-config --cppflags --cxxflags --ldflags --libs`
# Mac
else
	CC=clang++
	LIBS=-lSDL2 -framework OpenGL -framework Cocoa -lGLEW -stdlib=libc++ -lassimp
endif

#Compiler Flags
CXXFLAGS=-g -Wall -std=c++0x #`Magick++-config --cppflags --cxxflags --ldflags --libs`

# .o Compilation
O_FILES=main.o camera.o engine.o graphics.o object.o shader.o window.o tinyxml2.o physics.o

# Point to includes of local directories
INDLUDES=-I../include -I/usr/include/x86_64-linux-gnu/ImageMagick-6/ -I/usr/include/ImageMagick-6/ -I/usr/include/bullet

all: $(O_FILES)
	$(CC) $(CXXFLAGS) -o PA8 $(O_FILES) $(LIBS) #$(PATHI) $(PATHL)

main.o: ../src/main.cpp
	$(CC) $(CXXFLAGS) -c ../src/main.cpp -o main.o $(INDLUDES)

camera.o: ../src/camera.cpp
	$(CC) $(CXXFLAGS) -c ../src/camera.cpp -o camera.o $(INDLUDES)

engine.o: ../src/engine.cpp
	$(CC) $(CXXFLAGS) -c ../src/engine.cpp -o engine.o $(INDLUDES)

graphics.o: ../src/graphics.cpp
	$(CC) $(CXXFLAGS) -c ../src/graphics.cpp -o graphics.o $(INDLUDES)

object.o: ../src/object.cpp
	$(CC) $(CXXFLAGS) -c ../src/object.cpp -o object.o $(INDLUDES)

shader.o: ../src/shader.cpp
	$(CC) $(CXXFLAGS) -c ../src/shader.cpp -o shader.o $(INDLUDES)

window.o: ../src/window.cpp
	$(CC) $(CXXFLAGS) -c ../src/window.cpp -o window.o $(INDLUDES)

tinyxml2.o: ../src/tinyxml2.cpp
	$(CC) $(CXXFLAGS) -c ../src/tinyxml2.cpp -o tinyxml2.o $(INDLUDES)

physics.o: ../src/physics.cpp
	$(CC) $(CXXFLAGS) -c ../src/physics.cpp -o physics.o $(INDLUDES)

clean:
	-@if rm *.o PA8 2>/dev/null || true; then echo "Main Removed"; else echo "No Main"; fi
