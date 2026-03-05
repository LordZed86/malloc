# Build the malloc301 program
CC = gcc
CFLAGS = -Wall -g

#all: test.c memalloc.c memdebug.c
#	gcc test.c memalloc.c memdebug.c -o all
#	./all

test: test.c memalloc.c memdebug.c
  gcc test.c memalloc.c memdebug.c -o test
  ./test

dist:

clean:
