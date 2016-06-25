CC= g++
CFLAGS= -std=c++11 -Wall -O3
LINK= -lGL -lGLEW -lSDL2
LINK_OBJ= bin/SDL_Context.o bin/Engine.o \
		  bin/Shader.o bin/ShaderProgram.o 

all: SDL_Context Shader ShaderProgram Engine test

test:
	$(CC) $(CFLAGS) $@.cpp -o bin/main $(LINK_OBJ) -lGL -lGLEW -lSDL2 

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

# Other

window:
	$(CC) $(CFLAGS) stuff/examples/$@.cpp -o bin/main $(LINK_OBJ) -lGL -lGLEW -lSDL2

basic_test:
	$(CC) $(CFLAGS) stuff/examples/$@.cpp -o bin/main $(LINK_OBJ) -lGL -lGLEW -lSDL2

Math: test

