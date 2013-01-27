#include <stdio.h>
#include "list.h"

int main() {
    
    linked_list_t list;
    linked_list_init(&list);
    
    linked_list_add(&list, 'a');
    linked_list_add(&list, 'b');
    linked_list_add(&list, 'c');
    
    linked_list_traverse(&list, print_list);
    
    linked_list_free(&list);
    return 0;
}