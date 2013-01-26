// inspiration: http://www.lemoda.net/c/doubly-linked-list/

/*
basic usage:

#include <stdio.h>
#include "list.h"
int main() {

    line_node * file = NULL;
    char ch;
    FILE *f;
    
    f = fopen("abc.txt", "r");
    
    while ( (ch = fgetc(f)) != EOF ) {
        line_node_append( &file, ch );
    }
    
    line_traverse(file);  
    
    return 0;
}
*/

#include <stdio.h>
#include <stdlib.h>

#ifndef ADD_H_GUARD
#define ADD_H_GUARD

typedef struct line_node_t line_node;
typedef struct node_t node;

struct node_t {
  char data;
	node * next;
};

struct line_node_t {
	node * head;
	line_node * next;
};

void list_append(node ** head, char data) {

	node * current = *head;
    node * new_node = malloc(sizeof(node));

    // If list is empty
	if (current == NULL) {
        // Put head somewhere in the memory
        *head = malloc(sizeof(node));
        (*head)->data = data;
        (*head)->next = NULL;
	} else {
        // Search the last one
        while (current->next != NULL) {
            current = current->next;
        }

        new_node->data = data;
        new_node->next = NULL;
        current->next = new_node;
    }
}

char last_char = -1;

void line_node_append(line_node ** line_head, char data) {

    line_node * new_node = NULL;
    line_node * current = *line_head;

    if (*line_head == NULL) {
        *line_head = (line_node *)malloc(sizeof(line_node));
        
        (*line_head)->head = malloc(sizeof(node));
        (*line_head)->head->data = data;
        (*line_head)->head->next = NULL;
    } else {
        while (current->next != NULL) {
            current = current->next;
        }
        
        if (last_char == '\n') {
            new_node = (line_node *)malloc(sizeof(line_node));
            new_node->head = malloc(sizeof(node));
            new_node->head->data = data;
            new_node->head->next = NULL;
            current->next = new_node;
        } else {
            list_append( &current->head, data);
        } 
    }
    
    last_char = data;
}

void print_char(void * ch) {
	printf("%c", *(char *)ch);
}

void list_traverse(node * head, void (*callback)(void * data)) {
    node * current = head;

    if (current != NULL) {

    	// If this is the first or the only element
    	if (current->next != NULL) {
    		callback(&current->data);
    		current = current->next;
    	}

    	// Iterate for the rest of the list
    	while (current != NULL) {
    		callback(&current->data);
    		current = current->next;
    	}
    } else {
    	printf("This list is empty.\n");
    }
}


void line_traverse (void * line_head) {
    line_node * current = line_head;
    int i = 1;
    
    while (current != NULL) {
        printf("%d  ", i++);
        list_traverse(current->head, print_char);
        current = current->next;
    }
}

#endif
