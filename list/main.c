/**
 * TODO
 * - Tratar o delete
 * - Adicionar com x, y
 * - Print com limite
 */
#include <stdio.h>
#include <stdlib.h>

/* Link */
typedef struct link link_t;

struct link {
    char data;
    link_t * prev;
    link_t * next;
};

/* Lista encadeada */
typedef struct linked_list {
    link_t * first;
    link_t * last;
} linked_list_t;

/* Inicialização da lista encadeada */
void linked_list_init(linked_list_t * list)
{
    list->first = list->last = 0;
}

/* Adicionar */
void linked_list_add(linked_list_t * list, char data)
{
    link_t * link;

    /* calloc() já define o próximo (next) como zero. */
    link = calloc(1, sizeof(link_t));

    if (!link) {
        fprintf(stderr, "calloc failed.\n");
        exit(EXIT_FAILURE);
    }

    link->data = data;

    if (list->last) {
        /* Juntar os dois links do final. */
        list->last->next = link;
        link->prev = list->last;
        list->last = link;
    } else {
        list->first = link;
        list->last = link;
    }
}

/* Remover */
void linked_list_delete(linked_list_t * list, link_t * link)
{
    link_t * prev;
    link_t * next;

    prev = link->prev;
    next = link->next;

    if (prev) {
        if (next) {
            /* Ambos os links anteriores e próximos são válidos, então apenas
                passar pelo "link" sem alterar a lista. */
            prev->next = next;
            next->prev = prev;
        } else {
            /* Somente o link anterior é válido, então "prev" (elemento anterior), 
                é agora o último link na lista */
            prev->next = 0;
            list->last = prev;
        }
    } else {
        if (next) {
            /* Somente o próximo link é válido, não o anterior, então o próximo
                é agora o primeiro link na lista. */
            next->prev = 0;
            list->first = next;
        } else {
            /* Nem o anterior nem o próximo são links válidos, então a lista está
                vazia agora. */
            list->first = 0;
            list->last = 0;
        }
    }

    free(link);
}

/* Atravessar */
void linked_list_traverse(linked_list_t * list/*, void (*callback) (char)*/)
{
    link_t * link;

    for (link = list->first; link; link = link->next) {
        printf("%c", link->data);
    }
}

/* Limpar a lista (free) */
void linked_list_free(linked_list_t * list)
{
    link_t * link;
    link_t * next;

    for (link = list->first; link; link = next) {
        /* Guardar o próximo valor para não acessarmos memória que já foi limpa. */
        next = link->next;
        free(link);
    }
}

/* Imprimir a lista */
void print_list(char data)
{
    printf("%c", data);
}

/** LINHA: LISTA ENCADEADA **/

/* Link */
typedef struct line_link line_link_t;

struct line_link {
    linked_list_t * head;
    line_link_t * prev;
    line_link_t * next;
};

/* Lista encadeada */
typedef struct line_linked_list {
    line_link_t * first;
    line_link_t * last;
} line_linked_list_t;

/* Inicialização da lista encadeada */
void line_linked_list_init(line_linked_list_t * list)
{
    list->first = list->last = 0;
}

/* Adicionar */
void line_linked_list_add(line_linked_list_t * list, char data)
{
    line_link_t * line_lnk;
    linked_list_t * linked_lst;

    // Alocação do novo nó (line_lnk)
    line_lnk = calloc(1, sizeof(line_link_t));

    // Verificar se line_lnk foi alocado
    if (!line_lnk) {
        fprintf(stderr, "calloc of line link failed.\n");
        exit(EXIT_FAILURE);
    }

    // Alocação da lista encadeada de caracteres
    linked_lst = calloc(1, sizeof(link_t));

    // Inicializando a lista encadeada
    linked_lst->first = linked_lst->last = 0;

    // Verificar se a linked_lst foi alocado
    if (!linked_lst) {
        fprintf(stderr, "calloc of line link failed.\n");
        exit(EXIT_FAILURE);
    }

    // Verificar se a lista não está vazia
    if (list->last) {
        // Criar um novo nó e colocar o caractere
        if (list->last->head->last->data == '\n') {
            // Criar a lista encadeada
            linked_list_add(linked_lst, data);

            // Juntar a lista encadeada ao link da linha
            line_lnk->head = linked_lst;

            // Colocar o link da linha no fim da lista
            list->last->next = line_lnk;
            line_lnk->prev = list->last;
            list->last = line_lnk;
        } else {
            // Colocar o caractere na linha
            linked_list_add(list->last->head, data);
        }
    } else {
        // Criar a lista encadeada
        linked_list_init(linked_lst);
        linked_list_add(linked_lst, data);

        // Juntar a lista encadeada no link da linha
        line_lnk->head = linked_lst;

        // Iniciar a lista
        list->first = line_lnk;
        list->last = line_lnk;
    }
}

/* Desalocara a lista encadeada de linha. */
void line_linked_list_free(line_linked_list_t * list)
{
    line_link_t * link;
    line_link_t * next;

    for (link = list->first; link; link = next) {
        /* Guardar o próximo valor para não acessarmos memória que já foi limpa. */
        next = link->next;
        linked_list_free(link->head);
        free(link);
    }    
}

/** FIM DA LISTA ENCADEADA DE LINHAS **/

int main() {

    line_linked_list_t file;
    line_link_t * line_lnk;
    link_t * lnk;
    line_linked_list_init(&file);

    line_linked_list_add(&file, 'a');
    line_linked_list_add(&file, 'b');
    line_linked_list_add(&file, '\n');
    line_linked_list_add(&file, 'c');    

    for (line_lnk = file.first; line_lnk; line_lnk = line_lnk->next) {
        linked_list_traverse(line_lnk->head);
    }

    line_linked_list_free(&file);    
    return 0;
}
