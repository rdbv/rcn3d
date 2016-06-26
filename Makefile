CC= g++
CFLAGS= -std=c++11 -Wall -O3
LINK= -lGL -lGLEW -lSDL2
LINK_OBJ= bin/SDL_Context.o bin/Engine.o \
		  bin/Shader.o bin/ShaderProgram.o  bin/TextureLoader.o 

all: SDL_Context Shader ShaderProgram Engine TextureLoader \
	 Transform \
	 test \
	 basic_test

test:
	$(CC) $(CFLAGS) $@.cpp -o main $(LINK_OBJ) -lGL -lGLEW -lSDL2 -lfreeimage

Engine:
	$(CC) $(CFLAGS) -c src/$@.cpp -o bin/$@.o 

SDL_Context:
	$(CC) $(CFLAGS) -c src/$@.cpp -o bin/$@.o

InputHandler:
	$(CC) $(CFLAGS) -c src/$@.cpp -o bin/$@.o

Shader:
	$(CC) $(CFLAGS) -c src/$@.cpp -o bin/$@.o

ShaderProgram:
	$(CC) $(CFLAGS) -c src/$@.cpp -o bin/$@.o

TextureLoader:
	$(CC) $(CFLAGS) -c src/$@.cpp -o bin/$@.o

Transform:
	$(CC) $(CFLAGS) -c src/$@.cpp -o bin/$@.o

# Other

window:
	$(CC) $(CFLAGS) stuff/examples/$@.cpp -o main $(LINK_OBJ) -lGL -lGLEW -lSDL2

basic_test:
	$(CC) $(CFLAGS) stuff/examples/$@.cpp -o main $(LINK_OBJ) \
		bin/InputHandler.o bin/Transform.o -lGL -lGLEW -lSDL2 -lfreeimage
Math: test

