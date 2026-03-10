/* test.c
 * Authors: Lore, Joe, Kellen
 * CS 301 - Malloc Project, Winter 2026
 * Testing and benchmarking program for the memory allocator.
 * 
 * Cannot test till we flesh out Debug files
 */ 

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "memalloc.h"
#include "memdebug.h"


// prints expected vs actual and returns false if they dont match
#define CHECK(expected, actual, msg)                    \
    printf("  %s: expected %d got %d -> %s\n",          \
           msg, expected, actual,                       \
           (expected == actual) ? "PASSED" : "FAILED"); \
    if (expected != actual)                             \
        return false;

#define HEAP_SIZE 2048

static void *heap_test;

// functions to test each of the functions in memalloc.c
bool init_test()
{
    printf("********** init_test **********\n");

// reset heap for fresh start
    init301(heap_test, HEAP_SIZE);
    
    printf("Initial heap state:\n");
    print_blocks();
    
    // after init there should be one free block of 2044 bytes
    // (2048 - 4 byte node header)
    node *head = get_heap_head();
    CHECK(2044, head->size << 2 , "initial heap size");
    
    printf("\n");
    return true;
}

bool malloc_test() {
    printf("=== malloc_test ===\n");
    
    // reset heap to clean state
    init301(heap_test, HEAP_SIZE);
    
    // test basic allocation
    void *a = malloc301(100);
    printf("After malloc301(100):\n");
    print_blocks();
    CHECK(100, sizeof301(a), "malloc 100 bytes");
    
    // test second allocation
    void *b = malloc301(200);
    printf("After malloc301(200):\n");
    print_blocks();
    CHECK(200, sizeof301(b), "malloc 200 bytes");
    
    // test rounding up to multiple of 4
    void *c = malloc301(7);
    printf("After malloc301(7) (should round to 8):\n");
    print_blocks();
    CHECK(8, sizeof301(c), "malloc 7 rounds to 8");
    
    // test invalid inputs
    void *d = malloc301(0);
    CHECK(0, (d == NULL ? 0 : 1), "malloc 0 returns NULL");
    
    void *e = malloc301(-1);
    CHECK(0, (e == NULL ? 0 : 1), "malloc -1 returns NULL");
    
    // test allocation too large
    void *f = malloc301(9999);
    CHECK(0, (f == NULL ? 0 : 1), "malloc too large returns NULL");
    
    printf("\n");
    return true;
}

bool calloc_test() {
    printf("=== calloc_test ===\n");
    
    // reset heap to clean state
    init301(heap_test, HEAP_SIZE);
    
    // test basic calloc
    void *a = calloc301(10, 4);
    printf("After calloc301(10, 4):\n");
    print_blocks();
    CHECK(40, sizeof301(a), "calloc 10*4 = 40 bytes");
    
    // test that memory is zeroed
    char *bytes = (char*)a;
    bool zeroed = true;
    for (int i = 0; i < 40; i++) {
        if (bytes[i] != 0) {
            zeroed = false;
            break;
        }
    }
    printf("  memory zeroed: expected 1 got %d -> %s\n",
        zeroed, zeroed ? "PASSED" : "FAILED");
    if (!zeroed) return false;
    
    // test invalid inputs
    void *b = calloc301(0, 4);
    CHECK(0, (b == NULL ? 0 : 1), "calloc 0 num returns NULL");
    
    void *c = calloc301(10, 0);
    CHECK(0, (c == NULL ? 0 : 1), "calloc 0 size returns NULL");
    
    void *d = calloc301(-1, 4);
    CHECK(0, (d == NULL ? 0 : 1), "calloc -1 num returns NULL");
    
    printf("\n");
    return true;
}  


int main (void){
    // create heap for testing
    heap_test = malloc(HEAP_SIZE);
    init301(heap_test, HEAP_SIZE);

    // Tests tor init301
    printf("init_test:   %s\n", init_test()   ? "PASSED" : "FAILED");

    // TODO: add tests for Malloc301
    printf("malloc_test: %s\n", malloc_test() ? "PASSED" : "FAILED");
    
    // TODO: add tests for calloc301
    printf("calloc_test: %s\n", calloc_test() ? "PASSED" : "FAILED");

    // free the heap block when done
    free(heap_test);
    return 0;
}