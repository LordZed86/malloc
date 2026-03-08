/*
 * memalloc.h
 * Authors: Lore, Joe, Kellen
 * CS 301 - Malloc Project
 * March 2026
 * Public inteface for the memory allocation library
 */

 #ifndef MEMALLOC_H
 #define MEMALLOC_H

#define NODE_SIZE 4

/*
 * Initializes the memory pool with the given block and size.
 * block: pointer to a valid memory region, size <= 256MB
 */
void init301(void* block, int size);

/* 
 * Allocates a block of at least 'size' bytes (rounded up to multiple of 4).
 * Uses first-fit strategy.
 * Returns NULL if size <= 0 or no block available.
 */
 void* malloc301(int size);
 

/* 
 * Allocates a zeroed block large enough for 'num' elements of 'size' bytes each.
 * Returns NULL if size <= 0 or no block available.
 */
void* calloc301(int num, int size);

/* 
 * Reallocates the block at p to the new size.
 * Copies existing data. Returns NULL if no block available.
 */
void* realloc301(void* p, int size);

/*
 *Frees the block at p and coalesces neighboring free blocks.
 * Does nothing if p is NULL.
 */
void free301(void* p);

/* 
 * Returns the allocated size in bytes of the block at p.
 * Returns 0 if p is NULL.
 */
int sizeof301(void* p);

#endif