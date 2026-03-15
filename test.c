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
#include "memops.h"

// add these defines at the top of test.c
#define RED     "\033[0;31m"
#define GREEN   "\033[0;32m"
#define RESET   "\033[0m"

// prints expected vs actual and returns false if they dont match
#define CHECK(expected, actual, msg) \
    printf("  %s: expected %d got %d -> %s\n", \
    msg, expected, actual, \
    (expected == actual) ? GREEN "PASSED" RESET : RED "FAILED" RESET); \
    if (expected != actual) return false;

#define HEAP_SIZE 2048

static void *heap_test;

// functions to test each of the functions in memalloc.c
bool init_test()
{
    printf("********** init_test **********\n\n");

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
    printf("********** malloc_test **********\n\n");
    
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
    printf("********** calloc_test **********\n\n");
    
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
        zeroed, zeroed ? GREEN "PASSED" RESET : RED "FAILED" RESET);
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

bool free_test() {
    printf("********** free_test **********\n\n");

    //reset heap to clean tate
    init301(heap_test, HEAP_SIZE);

    // Allocate 3 blocks to test free in both directions
    void *a = malloc301(100);
    void *b = malloc301(200);
    void *c = malloc301(300);

    printf("After three allocations (A=100, B=200, C=300);\n");
    print_blocks();
    // Checks to see if I did it right 
    CHECK(100, sizeof301(a), "A size");
    CHECK(200, sizeof301(b), "B size");
    CHECK(300, sizeof301(c), "C size");

    // free middle block B and test if it becomes free and coalesce forward
    free301(b);
    printf("After free301(B):\n");
    print_blocks();

    // check if A and C are still used because only B should have been free
    CHECK(100, sizeof301(a), "A size after freeing B");
    CHECK(300, sizeof301(c), "C size after freeing B");

    //Free C, should merge B and C into a single free block
    free301(c);
    printf("After free301(C) (Will coalesce with B):\n");
    print_blocks();

    void *d = malloc301(400);
    printf("After malloc301(400) into merged free space:\n");
    print_blocks();
    CHECK(400, sizeof301(d), "malloc 400 into merged B and C");

    //test backward coalescing by freeing A then D and verify space is changed
    free301(a);
    free301(d);
    printf("After free301(A) and free301(D) will coalesce all:");
    print_blocks();

    void *e = malloc301(HEAP_SIZE / 2);
    printf("After malloc301(HEAP_SIZE / 2) from fully coalesced free block:\n");
    print_blocks();
    CHECK(HEAP_SIZE / 2, sizeof301(e), "malloc large after full coalesce");

    // test NULL to see if it does nothing and doesn't crash.
    free301(NULL);
    printf("After free301(NULL) will be no-op\n");
    print_blocks();

    printf("\n");
    return true;
}

bool memset_test() {
    printf("********** memset_test **********\n\n");
    init301(heap_test, HEAP_SIZE);
    
    // test basic memset
    void *a = malloc301(20);
    memset301(a, 5, 20);
    
    // verify every byte is set to 5
    char *bytes = (char*)a;
    bool correct = true;
    for (int i = 0; i < 20; i++) {
        if (bytes[i] != 5) {
            correct = false;
            break;
        }
    }
    printf("  memset to 5: expected 1 got %d -> %s\n",
        correct, correct ? GREEN "PASSED" RESET : RED "FAILED" RESET);
    if (!correct) return false;

    // test memset to 0
    memset301(a, 0, 20);
    bool zeroed = true;
    for (int i = 0; i < 20; i++) {
        if (bytes[i] != 0) {
            zeroed = false;
            break;
        }
    }
    printf("  memset to 0: expected 1 got %d -> %s\n",
        zeroed, zeroed ? GREEN "PASSED" RESET : RED "FAILED" RESET);
    if (!zeroed) return false;

    // test NULL pointer returns NULL
    void *b = memset301(NULL, 5, 20);
    CHECK(0, (b == NULL ? 0 : 1), "memset NULL returns NULL");

    // test size <= 0 returns NULL
    void *c = memset301(a, 5, 0);
    CHECK(0, (c == NULL ? 0 : 1), "memset size 0 returns NULL");

    // test memset with max byte value 255
    memset301(a, 255, 20);
    bool maxed = true;
    for (int i = 0; i < 20; i++) {
        if ((unsigned char)bytes[i] != 255) {
            maxed = false;
            break;
        }
    }
    printf("  memset to 255: expected 1 got %d -> %s\n",
        maxed, maxed ? GREEN "PASSED" RESET : RED "FAILED" RESET);
    if (!maxed) return false;

    printf("\n");
    return true;
}

bool memcpy_test() {
    printf("********** memcpy_test **********\n\n");
    // Allocate 2 blocks
    void *a = malloc301(100);
    void *b = malloc301(200);
    printf("After two allocations (A=100, B=200);\n");
    print_blocks();

        // fill a with 1s and b with 2s
    memset301(a, 1, 100);
    memset301(b, 2, 200);
    printf("After memset A to 1s and B to 2s:\n");
    print_blocks();

    // copy a to b and verify first 100 bytes of b are now 1s
    memcpy301(b, a, 100);
    printf("After memcpy301(B, A, 100) (copy A to B):\n");
    print_blocks();
    printf("\n");
    
    return true;
}



int main (void){
    // create heap for testing
    heap_test = malloc(HEAP_SIZE);
    init301(heap_test, HEAP_SIZE);

    printf("init_test:   %s\n\n", init_test()   ? GREEN "PASSED" RESET : RED "FAILED" RESET);

    printf("malloc_test: %s\n\n", malloc_test() ? GREEN "PASSED" RESET : "FAILED" RESET);

    printf("free_test: %s\n\n", free_test() ? GREEN "PASSED" RESET : "FAILED" RESET);
    
    printf("calloc_test: %s\n\n", calloc_test() ? GREEN "PASSED" RESET : "FAILED" RESET);

    printf("memset_test: %s\n\n", memset_test() ? GREEN "PASSED" RESET : RED "FAILED" RESET);

    printf("memcpy_test: %s\n\n", memcpy_test() ? GREEN "PASSED" RESET : RED "FAILED" RESET);

    // free the heap block when done
    free(heap_test);
    return 0;
}