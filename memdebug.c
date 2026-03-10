
/* 
 * memdebug.c
 * Authors: Lore, Joe, Kellen
 * CS 301 - Malloc Project
 * March 2026
 * Implements debugging utility functions for the memory allocator.
 */

#include "memimpl.h"
#include "memdebug.h"
#include "memalloc.h"

 /*
 * Prints debugging information about a single block,
 * including address, status, and size.
 * Example output: [0x22c8d0, used, 512B]
 */

 
void print_block(void* block) {
    node* temp = (node*)((char*)block - NODE_SIZE);
    bool used = temp->free;
    printf("[%p, %s, %dB]\n", block, used ? "free" : "used", temp->size << 2);
}

/*
 * Prints debugging information about all blocks in the heap,
 * numbered with 2-digit right-aligned fields.
 * Example output:
 *  01 [0x22c8c4, used, 8B]
 *  02 [0x22c8d0, free, 512B]
 */
void print_blocks(void) {
    node* current = get_heap_head();
    int count = 1;
    while (current != NULL) {
        printf("%2d: ", count);
        print_block((char*)current + NODE_SIZE);
        count++;
        if(current->last){
            current = NULL;
        }else{
           current = (node*)((char*)current + NODE_SIZE + (current->size << 2)); 
        }
    }
}

