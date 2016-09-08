/********************************************************************
 *  Nomes: Gabriel Capella                       Números USP: 8962078 
 *         Luís Felipe de Melo Costa Silva                    9297961
 * 
 *  Arquivo:   collector.c
 *  Descrição: Implementa as funções da biblioteca collector.h
 ********************************************************************/   

#include "collector.h"

struct reserved {
    void  * add;
    struct reserved * next;
};
typedef struct reserved * R;

static R head = NULL;

void * malloc2 (int size) {
    R new;
    new = malloc (sizeof(struct reserved));
    new->add = malloc(size);
    new->next = head;
    head = new;
    return new->add;
}

void * realloc2 (void *value, int size) {
    R new;
    new = malloc (sizeof(struct reserved));
    new->add = realloc (value, size);
    new->next = head;
    head = new;
    return new->add;
}

void free_all () {
    R tmp;
    while (head != NULL) {
        free (head->add);
        tmp = head;
        head = head->next;
        free (tmp);
    }
}
