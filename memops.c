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
    if ( to != NULL && from != NULL && size > 0) {
      //
    }
  }

 /*
  * Sets size bytes starting at p to the value ch.
  * Returns p, or NULL if p is NULL or size <= 0.
  */
  void* memset301(void* p, int ch, int size){
    if ( p == NULL || size <= 0) {
      return NULL;
    }
    return p;
  }

/*
  * Sets size bytes starting at p to zero.
  * Returns p, or NULL if p is NULL or size <= 0.
  */
  void* memzero301(void* p, int size){
    if ( p == NULL || size <= 0) {
      return NULL;
    }
    // cast p to char* to manipulate individual bytes
    char* bytep = (char*)p;
    // now loop through each byte and set to zero each time
    for (int i = 0; i < size; i++) {
      bytep[i] = 0;
    }
    return p;
  }