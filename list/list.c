/**
 * TODO
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

/* Desalocar a lista encadeada de linha. */
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

/** OPERACOES COM ARQUIVO **/

/* Carregar arquivo para a lista */
void list_load_from_file(char * file_name, line_linked_list_t * list)
{
    FILE * fp = fopen(file_name, "r");
    char ch;
    
    // Verificar se o arquivo existe.
    if (fp != NULL) {
        // Varrer todo o arquivo e colocar cada elemento na lista.
        while ((ch = fgetc(fp)) != EOF) {
            line_linked_list_add(list, ch);
        }
    }
    
    fclose(fp);
}

/* Salvar lista em arquivo */
void list_save_to_file(line_linked_list_t * list, char * file_name)
{
    FILE * fp = fopen(file_name, "w");
    line_link_t * line_lnk;
    link_t * link;

    // Percorrer as linhas
    for (line_lnk = list->first; line_lnk; line_lnk = line_lnk->next) {
        // Percorrer as colunas
        for (link = line_lnk->head->first; link; link = link->next) {
            // Savlar em arquivo
            fputc(link->data, fp);
        }
    }
    
    fclose(fp);
}

/** FIM OPERACOES COM ARQUIVO **/

int list_size(line_linked_list_t * list)
{
    line_link_t * line_lnk = list->first;;
    int size = 0;

    while (line_lnk) {
        size++;
        line_lnk = line_lnk->next;
    }
    
    return size;
}

void add_xy(line_linked_list_t * list, int x, int y, char data)
{
    int i, j;
    line_link_t * line_lnk = list->first;
    link_t * lnk, * new_lnk;
    
    line_link_t * new_line_lnk;
    linked_list_t * new_linked_list;
    linked_list_init(new_linked_list);
    
    // Percorrer o eixo X (linhas)
    for (i = 1; i < x; i++) {
        line_lnk = line_lnk->next;
    }
    
    // Percorrer o eixo Y (colunas)
    lnk = line_lnk->head->first;
    for (j = 1; j < y; j++) {
        lnk = lnk->next;
    }
    
    // Tratar o BACKSPACE
    if (data == 10) {
        linked_list_delete(line_lnk->head, lnk->prev);
    } else {
        // O elemento não é o último
        if (lnk->next) {
            // Quebrar a linha e criar uma nova caso seja \n
            if (data == '\n') {
                new_linked_list->first = lnk;
                new_linked_list->last = line_lnk->head->last;
            
                lnk->prev->next = 0;
                line_lnk->head->last = lnk->prev;
                linked_list_add(line_lnk->head, '\n');
            
                new_line_lnk = calloc(1, sizeof(line_link_t));
                new_line_lnk->head = new_linked_list;

                line_lnk->next = new_line_lnk;
                new_line_lnk->prev = line_lnk;
                new_line_lnk->next = 0;

                list->last = new_line_lnk;
            } else {
                new_lnk = calloc(1, sizeof(link_t));
                new_lnk->data = data;
                
                lnk->next->prev = new_lnk;
                new_lnk->next = lnk->next;
                new_lnk->prev = lnk;
                lnk->next = new_lnk;
            }
        } else { // É o útimo elemento
            linked_list_add(line_lnk->head, data);
        }
    }
}

int main()
{
    line_linked_list_t file;
    line_link_t * line_lnk;
    link_t * lnk;
    line_linked_list_init(&file);
    
    list_load_from_file("teste.txt", &file);
    
    for (line_lnk = file.first; line_lnk; line_lnk = line_lnk->next) {
        linked_list_traverse(line_lnk->head);
    }
    
    list_save_to_file(&file, "save.txt");

    printf("\n%d\n", list_size(&file));

    line_linked_list_free(&file);    
    return 0;
}
