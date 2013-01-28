#ifndef ADD_H_GUARD
#define ADD_H_GUARD

/* Link */
typedef struct line_link line_link_t;

struct line_link {
    linked_list * head;
    line_link_t * prev;
    line_link_t * next;
};

/* Linked list */
typedef struct line_linked_list {
    line_link_t * first;
    line_link_t * last;
} line_linked_list_t;

#endif