#include <stdio.h>
#include <stdlib.h>

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
    link = calloc(1, sizeof(link_t));
    
    if (!link) {
        fprintf(stderr, "calloc failed.\n");
        exit(EXIT_FAILURE);
    }
    
    link->data = data;

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

/* Delete */
void linked_list_delete(linked_list_t * list, link_t * link)
{
    link_t * prev;
    link_t * next;
    
    prev = link->prev;
    next = link->next;
    
    if (prev) {
        if (next) {
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
        if (next) {
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

/* Traverse */
void linked_list_traverse(linked_list_t * list, void (*callback) (char))
{
    link_t * link;
    
    for (link = list->first; link; link = link->next) {
        callback(link->data);
    }
}

/* Free list */
void linked_list_free(linked_list_t * list)
{
    link_t * link;
    link_t * next;
    
    for (link = list->first; link; link = next) {
        /* Store the next value so that we don't access freed memory */
        next = link->next;
        free(link);
    }
}

/* Print list */
void print_list(char data)
{
    printf("%c", data);
}

/** LINE LINKED LIST **/

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
void line_linked_list_init(line_linked_list_t * list)
{
    list->first = list->last = 0;
}

/* Add */
void line_linked_list_add(line_linked_list_t * list, char data)
{
    line_link_t * line_lnk;
    linked_list_t linked_lst;

    line_lnk = calloc(1, sizeof(line_link_t));

    if (!list) {
        fprintf(stderr, "calloc failed.\n");
        exit(EXIT_FAILURE);
    }
    
    if (list->last) {
        if (list->last->head->last->data == '\n') {
            // Create a new node and put the char
            
            // Create a linked list
            linked_list_init(&linked_lst);
            linked_list_add(&linked_lst, data);
            
            // Attach the linked list to the line link
            line_lnk->head = &linked_lst;
            
            // Put the line link in the end of the list
            list->last->next = line_lnk;
            line_lnk->prev = list->last;
            list->last = line_lnk;
        } else {
            // Append the char in the line
            linked_list_add(list->last->head, data);
        }
    } else {
        // Create linked list
        linked_list_init(&linked_lst);
        linked_list_add(&linked_lst, data);
        
        // Attach the linked list to the line link
        line_lnk->head = &linked_lst;
        
        // Set the list
        list->first = line_lnk;
        list->last = line_lnk;
    }
}

/* Line linked list traverse */
void line_linked_list_traverse(line_linked_list_t * list);

/** END OF LINE LINKED LIST **/

int main() {
    
    line_linked_list_t file;
    line_link_t * line_lnk;
    link_t * lnk;
    line_linked_list_init(&file);
    
    line_linked_list_add(&file, '\n');
    line_linked_list_add(&file, 'a');
    line_linked_list_add(&file, 'b');
    
    return 0;
}