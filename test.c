/* test.c
 * Authors: Lore, Joe, Kellen
 * CS 301 - Malloc Project, Winter 2026
 * Testing and benchmarking program for the memory allocator.
 * 
 * Cannot test till we flesh out Debug files
 */ 

#include <stdio.h>
#include "memalloc.h"
#include "memdebug.h"
#include <stdio.h>
#include <stdbool.h>

// functions to test each of the functions in memalloc.c
bool init_test() {
    
}

bool malloc_test() {
    return true;
}

bool calloc_test() {
    return true;
}  

//lelee
int main (void){
    // TODO: add tests tor init301
    init_test();
    // TODO: add tests for Malloc301
    malloc_test();
    // TODO: add tests for calloc301
    calloc_test();

    printf("%s", "Hello World");
}