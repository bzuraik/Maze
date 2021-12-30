CC = gcc
CFLAGS = -std=c11 -g

all: maze

maze: maze.c
	$(CC) $(CFLAGS) maze.c -o maze
	$(CC) $(CFLAGS) -fopenmp maze.c -o mazep

clean:
	rm maze mazep *.o *.a