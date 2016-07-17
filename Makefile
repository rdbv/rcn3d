CC= g++
CFLAGS= -std=c++11 -Wall -O3
LINK= -lGL -lGLEW -lSDL2 -lfreeimage 
LINK_OBJ= bin/Chunk.o

all: Chunk test


test:
	$(CC) $(CFLAGS) $@.cpp -o main \
		$(LINK_OBJ) \
		-lGL -lGLEW -lSDL2 -lfreeimage


Chunk:
	$(CC) $(CFLAGS) -c src/$@.cpp -o bin/Chunk.o 

# Other

basic:
	$(CC) $(CFLAGS) stuff/examples/$@.cpp -o main $(LINK_OBJ) $(LINK)


