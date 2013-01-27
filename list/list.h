#include <stdlib.h>
#include <stdio.h>

#ifndef ADD_H_GUARD
#define ADD_H_GUARD

/* Link */
typedef struct link link_t;

struct link {
    char data;
    link_t * prev;
    link_t * next;
};

/* Linked list */
typedef struct linked_list {
    link_t * first;
    link_t * last;
} linked_list_t;

/* Linked list init */
void linked_list_init(linked_list_t * list) 
{    
    list->first = list->last = 0;
}

/* Add */
void linked_list_add(linked_list_t * list, char data) 
{
    link_t * link;
    
    /* calloc sets the "next" field to zero. */
    link = calloc( 1, sizeof(link_t) );
    
    if ( !link ) {
        fprintf(stderr, "calloc failed.\n");
        exit(EXIT_FAILURE);
    }
    
    link->data = data;
    
    if ( list->last ) {
        /* Join the two final links together. */
        list->last->next = link;
        link->prev = list->last;
        list->last = link;
    } else {
        list->first = link;
        list->last = link;
    }    
}

/* Delete */
void linked_list_delete(linked_list_t * list, link_t * link)
{
    link_t * prev;
    link_t * next;
    
    prev = link->prev;
    next = link->next;
    
    if ( prev ) {
        if ( next ) {
            /* Both the previous and next links are valid, so just
                bypass "link" without altering "list" at all */
            prev->next = next;
            next->prev = prev;
        } else {
            /* Only the previous link is valid, so "prev" is now the
                last link in the "list". */
            prev->next = 0;
            list->last = prev;
        }
    } else {
        if ( next ) {
            /* Only the next link is valid, not the previous one, so
                "next" is now the first link in "list". */
            next->prev = 0;
            list->first = next;
        } else {
            /* Neither previous nor next links are valid, so the list
                is now empty. */
            list->first = 0;
            list->last = 0;
        }
    }
    
    free(link);
}

#endif