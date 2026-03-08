
/* 
 * memdebug.c
 * Authors: Lore, Joe, Kellen
 * CS 301 - Malloc Project
 * March 2026
 * Implements debugging utility functions for the memory allocator.
 */

#include "memimpl.h"
#include "memdebug.h"

 /*
 * Prints debugging information about a single block,
 * including address, status, and size.
 * Example output: [0x22c8d0, used, 512B]
 */
void print_block(void* block){
    bool used = 0; //check used somehow
    //some loop to get used
    printf("[%p, %s, %d]", block, used ? "used" : "free", block->size);

}

/*
 * Prints debugging information about all blocks in the heap,
 * numbered with 2-digit right-aligned fields.
 * Example output:
 *  01 [0x22c8c4, used, 8B]
 *  02 [0x22c8d0, free, 512B]
 */
void print_blocks(void){
    //for loop to go through entire heap
    for (int i = 0; i < 10; i++) { //change to size of heap contents
        bool used = 0; //check used
        printf("%d [%p, %s, %d]", i, block, used ? "used" : "free", block->size);
    }
    
}