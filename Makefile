CC= g++
CFLAGS= -std=c++11 -Wall -O0
LINK= -lGL -lGLEW -lSDL2 -lfreeimage 
LINK_OBJ= bin/SDL_Context.o bin/Engine.o \
		  bin/Shader.o bin/ShaderProgram.o \
		  bin/TextureLoader.o bin/Renderer.o \
		  bin/Transform.o bin/InputHandler.o

all: SDL_Context Shader ShaderProgram Engine \
	 TextureLoader Transform Renderer InputHandler \
	 test basic_test

test:
	$(CC) $(CFLAGS) $@.cpp -o main $(LINK_OBJ) -lGL -lGLEW -lSDL2 -lfreeimage 

test1:
	$(CC) $(CFLAGS) $@.cpp -o main  -lassimp

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

Renderer:
	$(CC) $(CFLAGS) -c src/$@.cpp -o bin/$@.o

# Other

window:
	$(CC) $(CFLAGS) stuff/examples/$@.cpp -o main $(LINK_OBJ) -lGL -lGLEW -lSDL2

basic_test:
	$(CC) $(CFLAGS) stuff/examples/$@.cpp -o main $(LINK_OBJ) $(LINK) 

basic_refactored:
	$(CC) $(CFLAGS) stuff/examples/$@.cpp -o main $(LINK_OBJ) $(LINK)

Math: test

