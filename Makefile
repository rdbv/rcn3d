CC= g++
CFLAGS= -std=c++11 -Wall -O3 
LINK= -lGL -lGLEW -lSDL2
LINK_OBJ= bin/SDL_Context.o bin/InputHandler.o bin/Engine.o

all: SDL_Context InputHandler Engine \
	test

test:
	$(CC) $(CFLAGS) src/$@.cpp -o bin/main $(LINK_OBJ) -lGL -lGLEW -lSDL2 

Engine:
	$(CC) $(CFLAGS) -c src/$@.cpp -o bin/$@.o 

SDL_Context:
	$(CC) $(CFLAGS) -c src/$@.cpp -o bin/$@.o

InputHandler:
	$(CC) $(CFLAGS) -c src/$@.cpp -o bin/$@.o

# Other

Matrix: test

math_new:
	$(CC) $(CFLAGS) stuff/examples/$@.cpp -o bin/main

Math: test
