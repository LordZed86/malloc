/* 
 * memops.c
 * Authors: Lore, Joe, Kellen
 * CS 301 - Malloc Project
 * March 2026
 * Implements bulk memory operations: memcpy301, memset301, memzero301.
 */

#include "memimpl.h"
#include "memops.h"

 /*
  * Copies size bytes from from to to.
  * Assumes regions do not overlap.
  * Does nothing if size <= 0 or either pointer is NULL.
  */
  void memcpy301(void* to, void* from, int size){
    if ( to != NULL && from != NULL && size >= 0) {
      char* first = (char*)to;
      const char* second = (const char*)from;
      for (int i = 0; i < size; i++) {
        first[i] = second[i];
      }
    }
  }

 /*
  * Sets size bytes starting at p to the value ch.
  * Returns p, or NULL if p is NULL or size <= 0.
  */
  void* memset301(void* p, int ch, int size){
    if (p == NULL || size <= 0) return NULL;
    
    // cast to char* to move through memory one byte at a time
    char* ptr = (char*)p;
    
    // set each byte to ch one at a time
    for (int i = 0; i < size; i++) {
        ptr[i] = (char)ch;
    }
    return p;
  }

/*
  * Sets size bytes starting at p to zero.
  * Returns p, or NULL if p is NULL or size <= 0.
  */

  // we could probably just call memset(p, 0, size) which would cut down on redundance. that is if my memset is done right i guess.
  void* memzero301(void* p, int size){
    if ( p == NULL || size <= 0) {
      return NULL;
    }
    memeset301(p, 0, size);
    return p;
  }