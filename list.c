/*
 * Kellen Jones
 * CS 301 Winter 2026 | Project 4.3 - T9
 *
 * Changes from Project 3 - List the ways... Part 3:
 *
 *  - append_item() was added. The original list only supported inserting
 *    at the front or at an index. append_item() was needed by trie.c to
 *    build word lists in order when loading from the dictionary file.
 *
 *  - print_list() was updated to print in bracket format [word1, word2, ...]
 *    with a trailing newline. The original printed words space-separated
 *    with no brackets and no newline. The new format matches the expected
 *    T9 simulator output.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

void create_list(list *l) {
    l->head = NULL;
    l->size = 0;
}

bool empty_list(list *l) {
    return l->size == 0;
}

int size(list *l) {
    return l->size;
}

void *get(int i, list *l) {
    if (i < 0 || i >= l->size)
        return NULL;
    node *p = l->head;
    for (int k = 0; k < i; k++) {
        p = p->next;
    }
    return p->item;
}

void set_item(list *l, int i, void *item) {
    if (i < 0 || i >= l->size)
        return;

    node *p = l->head;
    for (int k = 0; k < i; k++)
        p = p->next;

    p->item = item;
}

void insert_item(list *l, void *item) {
    node *n = malloc(sizeof(node));
    n->item = item;
    n->next = l->head;

    l->head = n;
    l->size += 1;
}

void insert_at(list *l, int index, void *item) {
    if (index < 0 || index > l->size)
        return;

    if (index == 0) {
        insert_item(l, item);
        return;
    }

    node *p = l->head;
    for (int k = 0; k < index - 1; k++)
        p = p->next;

    node *n = malloc(sizeof(node));
    n->item = item;
    n->next = p->next;
    p->next = n;

    l->size += 1;
}

// added for Project 4.2 - walks to tail before inserting
void append_item(list *l, void *item) {
    node *n = malloc(sizeof(node));
    n->item = item;
    n->next = NULL;

    if (l->head == NULL) {
        l->head = n;
    } else {
        node *p = l->head;
        while (p->next != NULL)
            p = p->next;
        p->next = n;
    }

    l->size += 1;
}

void *remove_item(list *l) {
    if (l->head == NULL)
        return NULL;

    node *tmp = l->head;
    void *removed = tmp->item;

    l->head = tmp->next;
    free(tmp);
    l->size -= 1;

    return removed;
}

void *remove_at(list *l, int index) {
    if (index < 0 || index >= l->size)
        return NULL;

    if (index == 0) {
        return remove_item(l);
    }

    node *p = l->head;
    for (int k = 0; k < index - 1; k++)
        p = p->next;

    node *tmp = p->next;
    void *removed = tmp->item;

    p->next = tmp->next;
    free(tmp);
    l->size -= 1;

    return removed;
}

// updated for Project 4.2 - bracket format with trailing newline
void print_list(list *l) {
    printf("[");
    node *p = l->head;
    while (p != NULL) {
        printf("%s", (char *)p->item);
        if (p->next != NULL) printf(", ");
        p = p->next;
    }
    printf("]\n");
}

// insertion sort - operates directly on existing nodes, no copies
void sort_list(list *l) {
    if (l->head == NULL || l->head->next == NULL)
        return;

    node *sorted = NULL;
    node *current = l->head;

    while (current != NULL) {
        node *next = current->next;

        if (sorted == NULL || strcmp(current->item, sorted->item) < 0) {
            current->next = sorted;
            sorted = current;
        } else {
            node *p = sorted;
            while (p->next != NULL &&
                   strcmp(p->next->item, current->item) < 0) {
                p = p->next;
            }
            current->next = p->next;
            p->next = current;
        }
        current = next;
    }
    l->head = sorted;
}

void clear_list(list *l) {
    while (!empty_list(l)) {
        char *tmp = remove_item(l);
        free(tmp);
    }
}