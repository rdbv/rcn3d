CC= g++
CFLAGS= -std=c++11 -Wall -O0
LINK= -lGL -lGLEW -lSDL2 -lfreeimage 
LINK_OBJ= bin/SDL_Context.o \
		  bin/Shader.o bin/ShaderProgram.o \

all: SDL_Context Shader ShaderProgram \
	 test 

test:
	$(CC) $(CFLAGS) $@.cpp -o main \
		$(LINK_OBJ) \
		-lGL -lGLEW -lSDL2 -lfreeimage

SDL_Context:
	$(CC) $(CFLAGS) -c src/$@.cpp -o bin/$@.o

Shader:
	$(CC) $(CFLAGS) -c src/$@.cpp -o bin/$@.o

ShaderProgram:
	$(CC) $(CFLAGS) -c src/$@.cpp -o bin/$@.o

# Other

window:
	$(CC) $(CFLAGS) stuff/examples/$@.cpp -o main $(LINK_OBJ) -lGL -lGLEW -lSDL2

basic_refactored:
	$(CC) $(CFLAGS) stuff/examples/$@.cpp -o main $(LINK_OBJ) $(LINK)

basic:
	$(CC) $(CFLAGS) stuff/examples/$@.cpp -o main $(LINK_OBJ) $(LINK)

Math: test

