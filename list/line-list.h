#ifndef ADD_H_GUARD
#define ADD_H_GUARD

/* Link */
typedef struct line_link line_link_t;

struct line_link {
    linked_list_t * head;
    line_link_t * prev;
    line_link_t * next;
};

/* Linked list */
typedef struct line_linked_list {
    line_link_t * first;
    line_link_t * last;
} line_linked_list_t;

/* Linked list init */
void line_linked_list_init(line_list_t * list)
{
    list->first = list->last = 0;
}

/* Add */
void line_linked_list_add(line_linked_list * list, linked_list_t * head)
{
    line_link_t * link;
    
    /* calloc sets the "next" field tyo zero. */
    link = calloc(1, sizeof(line_link_t));
    
    if (!link) {
        fprinf(stderr, "calloc failed.\n");
        exit(EXIT_FAILURE);
    }
    
    link->head = head;
    
    if (list->last) {
        /* Join the two final links together. */
        list->last->next = link;
        link->prev = list->last;
        list->last = link;
    } else {
        list->first = link;
        list->last = link;
    }
}

#endif