/*
 * Kellen Jones
 * CS 301 Winter 2026 | Project 4.3 - T9
 *
 * Purpose:
 *   Provides a generic singly linked list data structure that stores
 *   void* items and supports insertion, removal, lookup, updating,
 *   printing, and sorting. The list maintains its own size and head
 *   pointer, allowing callers to manage collections of dynamically
 *   allocated items without exposing node details.
 *
 *   NOTE: This list doesn't manage the memory of stored items.
 *   Therefore, it is imperative to remember to manually allocate and free
 *   the data placed inside this List.
 *
 * * Remove all elements or clear the list before terminating the program *
 *
 * NOTE: Although the list stores void* items, print_list, sort_list, and clear_list
 * assume items are pointers to char*. Callers must ensure stored
 * values match these expectations, until a future update of this
 * implementation that addresses this issue.
 *
 * Changes from Project 3 - List the ways... Part 3:
 *
 *  - append_item() declaration added. Needed by trie.c to build word
 *    lists in dictionary order when loading from file.
 *
 *  - Removed <stdio.h>, <stdlib.h>, and <string.h> includes. These are
 *    implementation details and belong in list.c, not the header.
 *
 *  - print_list() comment updated to reflect new bracket format output.
 */

#ifndef LIST_H
#define LIST_H

#include <stdbool.h>

// Data structures

/*
 * node
 * Represents a single element in the linked list.
 * Fields:
 *   item - pointer to the stored value;
 *   next - pointer to the next node in the list.
 */
typedef struct node {
    void *item;
    struct node *next;
} node;

/*
 * list
 * Represents a singly linked list with a head pointer and size counter.
 * Fields:
 *   head - pointer to the first node (NULL if empty);
 *   size - number of elements currently in the list.
 */
typedef struct list {
    node *head;
    int size;
} list;

// Core Functions

/*
 * create_list(list *l)
 * Initializes an empty list by clearing the head pointer and size.
 * Parameters:
 *  l - the list to initialize.
 * Returns: nothing.
 * Special cases: none.
 */
void create_list(list *l);

/*
 * empty_list(list *l)
 * Determines whether the list contains zero elements.
 * Parameters:
 *  l - the list to check.
 * Returns: true if the list is empty; false otherwise.
 * Special cases: none.
 */
bool empty_list(list *l);

/*
 * size(list *l)
 * Retrieves the number of elements stored in the list.
 * Parameters:
 *  l - the list to query.
 * Returns: the list's size.
 * Special cases: none.
 */
int size(list *l);

/*
 * get(int i, list *l)
 * Retrieves the item stored at index i.
 * Parameters:
 *  i - index to access (0-based);
 *  l - the list to read from.
 * Returns: pointer to the item at index i.
 * Special cases: returns NULL if index is out of bounds.
 */
void *get(int i, list *l);

/*
 * set_item(list *l, int i, void *item)
 * Replaces the item stored at the given index in the list.
 * Parameters:
 *  l    - the list to modify;
 *  i    - position to update;
 *  item - new value to store.
 * Returns: nothing.
 * Special cases: does nothing if index is out of bounds.
 */
void set_item(list *l, int i, void *item);

/*
 * insert_item(list *l, void *item)
 * Inserts a new node at the front of the list.
 * Parameters:
 *  l    - the list to modify;
 *  item - value to store.
 * Returns: nothing.
 * Special cases: allocates memory for the new node;
 *  caller must free list later.
 */
void insert_item(list *l, void *item);

/*
 * insert_at(list *l, int index, void *item)
 * Inserts a new node at the given index in the list.
 * Parameters:
 *  l     - the list to modify;
 *  index - position to insert at;
 *  item  - value to store.
 * Returns: nothing.
 * Special cases: if index is 0, inserts at front in O(1);
 *  does nothing if index is out of bounds.
 */
void insert_at(list *l, int index, void *item);

/*
 * append_item(list *l, void *item)
 * Inserts a new node at the end (tail) of the list.
 * Added for Project 4.2 - needed by trie.c to build word lists in
 * dictionary order when loading from file.
 * Parameters:
 *  l    - the list to modify;
 *  item - value to store.
 * Returns: nothing.
 * Special cases: if the list is empty, behaves identically to insert_item.
 */
void append_item(list *l, void *item);

/*
 * remove_item(list *l)
 * Removes the first node from the list and returns its stored item.
 * Parameters:
 *  l - the list to modify.
 * Returns: pointer to removed item, or NULL if list is empty.
 * Special cases: frees the removed node; does not free the item.
 */
void *remove_item(list *l);

/*
 * remove_at(list *l, int index)
 * Removes the node at the given index and returns its stored item.
 * Parameters:
 *  l     - the list to modify;
 *  index - position to remove.
 * Returns: pointer to removed item, or NULL if index is invalid.
 * Special cases: index 0 delegates to remove_item.
 */
void *remove_at(list *l, int index);

/*
 * print_list(list *l)
 * Prints all string items stored in the list in bracket format: [word1, word2, ...]
 * Updated for Project 4.2 - original printed words space-separated with no
 * brackets and no newline.
 * Parameters:
 *  l - the list to print.
 * Returns: nothing.
 * Special cases: prints [] for an empty list.
 */
void print_list(list *l);

/*
 * sort_list(list *l)
 * Sorts string items in the list in lexical order using insertion sort.
 * Parameters:
 *  l - the list to sort.
 * Returns: nothing.
 * Special cases: does nothing for empty or single-element lists.
 */
void sort_list(list *l);

/*
 * clear_list(list *l)
 * Removes all nodes from the list and frees their stored char* items.
 * Parameters:
 *  l - the list to clear.
 * Returns: nothing.
 * Special cases: WILL NOT WORK FOR INTs or anything other than char*.
 */
void clear_list(list *l);

#endif // LIST_H