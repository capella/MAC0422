/* //////////////////////////////////////////////////////////////
// 
// Autor: Gabriel Capella
// Numero USP: 8962078
// Sigla: GABRIELC
// Data: 2015-10-13
// 
////////////////////////////////////////////////////////////// */
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
