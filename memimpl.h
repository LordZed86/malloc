/*
 * memimpl.h
 * Authors: Lore, Joe, Kellen
 * CS 301 - Malloc Project
 * March 2026
 * header for implementation details/structures not intended to be used publicly by clients
 */

#ifndef MEMIMPL_H
#define MEMIMPL_H

#include <stdio.h>
#include <stdbool.h>



/*
 * node
 * Represents a single element in the linked list.
 * Fields:
 *   size - stores size of memory block.
 *   free - stores if the memory block is in use or "free" (usable).
 *   last - stores if the node is the last memory block or not.
 */
typedef struct node {
    unsigned int size : 28; // 'size' occupies 28 bits
    unsigned int free : 1; // 'free' occupies 1 bit for free or not
    unsigned int last : 1; // 'last' occupies 1 bit for last block or not
    unsigned int padding : 2;// 2 more bits available to make 4 bytes alter or delete if we need to pack another field in there
} node;

/*
 * heap
 * global heap state.
 * Fields:
 *   head - points to the start of the memory pool
 *   total_size - the total size of the memory pool
 */
typedef struct heap { // 
    node *head;
    int total_size;
}heap;

#endif
