
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
void print_block(void* block) {
    bool used = block->free; //check used somehow
    //some loop to get used
    printf("[%p, %s, %dB]\n", block, used ? "used" : "free", block->size);

}

/*
 * Prints debugging information about all blocks in the heap,
 * numbered with 2-digit right-aligned fields.
 * Example output:
 *  01 [0x22c8c4, used, 8B]
 *  02 [0x22c8d0, free, 512B]
 */
void print_blocks(void) {
    //for loop to go through entire heap
    node* temp = heap->head;
    for (int i = 0; i < heap->total_size; i++) { //change to size of heap contents
        printf("%d: ", i);
        print_block(temp);
        temp = temp->next;
    }
    
}