/* 
 * memdebug.h
 * Authors: Lore, Joe, Kellen
 * CS 301 - Malloc Project
 * March 2026
 * header file .
 */

#ifndef MEMDEBUG_H
#define MEMDEBUG_H

// Prints debugging info about a single block (address, status, size).
void print_block(void* block);

// Prints debugging information about all blocks in the heap.
void print_blocks(void);

#endif