/*
 *
 */

#include <stdbool.h>

#include "memimpl.h"
#include "memalloc.h"

static heap* GLOBAL_HEAP;
static int NODE_SIZE = 4;

void init301(void* block, int size){
    
    GLOBAL_HEAP->head = block;
    GLOBAL_HEAP->total_size = size;

    node* start = block;

    start->size = size - NODE_SIZE;
    start->free = 1;
    start->last = 1;
}

void* malloc301(int size){
    return NULL;
}
 
void* calloc301(int num, int size){
    return NULL;

}

void* realloc301(void* p, int size){
    return NULL;
}

void free301(void* p){

}

int sizeof301(void* p){
    return 0;
}