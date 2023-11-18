CC = gcc
CFLAGS = -Wall -Wextra -Werror -ggdb -std=c99
OBJECTS = src/*.c
LIBS = -lSDL2 -lm

tetris: $(OBJECTS)
	$(CC) $(CFLAGS) -o tetris $(OBJECTS) $(LIBS)