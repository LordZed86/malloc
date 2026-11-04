# Makefile
# Authors: Lore, Joe, Kellen
# CS 301 - Malloc Project, Winter 2026
# Builds the malloc301 library and test program.

# Build the malloc301 program
CC = gcc
CFLAGS = -Wall -g
OBJS = memalloc.o memops.o memdebug.o

# Build everything
all: test

# Link test executable from object files
test: test.o $(OBJS)
	$(CC) $(CFLAGS) test.o $(OBJS) -o test

# Compile each source file into its object file
test.o: test.c memalloc.h memops.h memdebug.h
	$(CC) $(CFLAGS) -c test.c

memalloc.o: memalloc.c memalloc.h memimpl.h
	$(CC) $(CFLAGS) -c memalloc.c

memops.o: memops.c memops.h memimpl.h
	$(CC) $(CFLAGS) -c memops.c

memdebug.o: memdebug.c memdebug.h memimpl.h
	$(CC) $(CFLAGS) -c memdebug.c

# Create submission archive
dist:
	tar -czf cs301project.tar.gz *.c *.h Makefile README.md

# Remove build artifacts
clean:
	rm -f *.o test cs301project.tar.gz

# Memory leak tests

# Run test with valgrind (Linux or WSL)
valgrind: test
	valgrind --leak-check=full --track-origins=yes ./test

# Run test with leaks (Mac (apple silicon))
mac_leaks: test
	leaks --atExit -- ./test
