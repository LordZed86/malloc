/*
 * memalloc.c
 * Authors: Lore, Joe, Kellen
 * CS 301 - Malloc Project
 * March 2026
// for reference while we build this stuff, I think this fits better in the memimple notes with the strucst
 * **IMPORTANT**
 * Storing into node->size -> (divide by 4) shift >> right by 2
 * Reading from node->size -> (multiply by 4) shift << left by 2
 * Jumping to next node -> (multiply by 4) shift << left by 2
 */

#include <stdbool.h>
#include "memimpl.h"
#include "memalloc.h"

#define NODE_SIZE 4

static heap GLOBAL_HEAP;

//get the heap head node to pass to debug
node* get_heap_head(void) {
    return GLOBAL_HEAP.head;
}

void init301(void* block, int size){

    GLOBAL_HEAP.head = (node*)block;
    GLOBAL_HEAP.total_size = size;

    node* start = (node*)block;
    // subtract node header, shift right 2 to store as 4-byte units
    start->size = (size - NODE_SIZE) >> 2; 
    start->free = 1;
    start->last = 1;
}

void* malloc301(int size) {
    // return NULL if size is invalid
    if (size <= 0) return NULL;
    // round size up to nearest multiple of 4
    // add 3, shift right 2 (divide by 4), shift left 2 (multiply by 4)
    size = ((size + 3) >> 2) << 2;
    // start at the head of the block list
    node *current = GLOBAL_HEAP.head;
    while (current != NULL) {
        // check if block is free and large enough
        // shift left 2 to convert stored offset back to bytes
        if (current->free && (current->size << 2) >= size) {
            // calculate how many bytes would be left over after splitting
            // subtract requested size and node header size from total
            int leftover = (current->size << 2) - size - NODE_SIZE;
            
            if (leftover > NODE_SIZE) {
                // leftover is large enough to be worth splitting into a 
                // new block, place new node header directly after the 
                // allocated block
                node *next = (node*)((char*)current + NODE_SIZE + size);
                // store leftover size as offset (shift right 2 to divide by 4)
                next->size = leftover >> 2;
                next->free = 1;
                // new node inherits last status from current node
                next->last = current->last;
                // update current node size and mark as not last
                current->size = size >> 2;
                current->last = 0;
            }
            // mark block as in use and return pointer 
            // to memory after node header
            current->free = 0;
            return (char*)current + NODE_SIZE;
        }
        // move to next node or set NULL if this was the last node
        if (current->last) {
            current = NULL;
        } else { // jump forward by node header size plus block size in bytes
            current = (node*)((char*)current + NODE_SIZE + (
                current->size << 2));
        }
    }
    // no suitable block found
    return NULL;
}

void* calloc301(int num, int size){
    if (size <= 0) return NULL;
    // call malloc
    //allocate : num * size bytes
    // then call memzero //initialize all values to zero

    // no suitable block found
    return NULL;

}

// No actual idea why this is here but it's referenced so we ball I guess
void* realloc301(void* p, int size){
    return NULL;
}

void free301(void* p){
    if (p != NULL) {
        //
    }
    // if null do nothing
    // step back NODE_SIZE to point to the node
    // set node to free
    // check if next block is free and merge appropriatly
    // check if previous node is free and merge if needed - finding the previous
    // node is hard to do lol.

}

int sizeof301(void* p) {
    if (p == NULL) return 0;
    // step back NODE_SIZE bytes to get to the node header
    node *n = (node*)((char*)p - NODE_SIZE);
    // shift left 2 to convert stored offset back to bytes
    return n->size << 2;
}