
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
    node* temp = block;
    bool used = temp->free; 
    printf("[%p, %s, %dB]\n", block, used ? "used" : "free", temp->size);
}

/*
 * Prints debugging information about all blocks in the heap,
 * numbered with 2-digit right-aligned fields.
 * Example output:
 *  01 [0x22c8c4, used, 8B]
 *  02 [0x22c8d0, free, 512B]
 */
void print_blocks(void) {
    node* temp = get_heap_head();
    int count = 1;
    bool last = temp->last;
    while (!last) {
        printf("%d: ", count);
        print_block(temp);
        temp = temp >> temp->size; //move with >> bit operator not next //last thing to fix
        count++;
    }
    printf("%d: ", count);
    print_block(temp);
}