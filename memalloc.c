/*
 *
 */

#include <stdbool.h>

/*
 * node
 * Represents a single element in the linked list.
 * Fields:
 *   memory - pointer to the stored memory block;
 *   size - stores size of memory block
 *   free - stores if the memory block is in use or "free" (usable)
 *   next - pointer to the next node in the list.
 */
typedef struct node {
    void *memory;
    int size;
    bool free;
    struct node *next_block;
} node;

/*
 * block
 * 
 */
typedef struct block {
    node *head;
    int size;
    
}block;

void init301(void* block, int size){

}

void* malloc301(int size){

}
 
void* calloc301(int num, int size){

}

void realloc301(void* p, int size){

}

void free301(void* p){

}

int sizeof301(void* p){

}