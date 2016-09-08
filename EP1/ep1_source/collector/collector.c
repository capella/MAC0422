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

static R head;

void * malloc2 (int size) {
    R new;
    new = malloc (sizeof());
}

void * realloc2 (void *value, int size) {

}

int free_all (void * exec) {

}
