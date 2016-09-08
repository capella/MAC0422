/* //////////////////////////////////////////////////////////////
// 
// Autor: Gabriel Capella
// Numero USP: 8962078
// Sigla: GABRIELC
// Data: 2015-10-13
// 
////////////////////////////////////////////////////////////// */
#include "load-process.h"
#define MAX_PROCESS_NAME_SIZE 100

struct p_load {
    double  to;
    char    * name;
    double   dt;
    double  deadline;
    int     line;
};
typedef struct p_load * Load;

Load *lista;
int size, max_size, remaning;
int (*func) (void *);

void load_file (void *filename, int (*f) (void *)) {
    FILE *entrada;
    Load novo;
    Load *tmp_lista;
    double tmp_to, tmp_dt, tmp_deadline;
    char *tmp_name;
    char *name;

    func = f;

    name = (char*)filename;

    entrada = fopen (name, "r");
    size = 0;
    max_size = 10;

    lista = malloc2 (sizeof(Load) * max_size);
    tmp_name = malloc2 (MAX_PROCESS_NAME_SIZE * sizeof(char));

    while (1) {
        if (fscanf(entrada, "%lf", &tmp_to) == EOF) break;
        if (fscanf(entrada, "%s", tmp_name) == EOF) break;
        if (fscanf(entrada, "%lf", &tmp_dt) == EOF) break;
        if (fscanf(entrada, "%lf", &tmp_deadline) == EOF) break;

        size++;
        if (size > max_size) {
            max_size *= 2;
            tmp_lista = realloc2 (lista, max_size * sizeof(Load));
            lista = tmp_lista;
        }
        novo = malloc2(sizeof(struct p_load));
        novo->to = tmp_to;
        novo->dt = tmp_dt;
        novo->deadline = tmp_deadline;
        novo->name = tmp_name;
        novo->line = size-1;
        tmp_name = malloc2 (MAX_PROCESS_NAME_SIZE * sizeof(char));
        lista[size-1] = novo;
    }
    remaning = size;

    /* fprintf(stderr, "Arquivo carregado!\n"); */
}

/* função que chama, e funcao a ser chamada 
void *(void (*)(char *, int, int (*)(void*), void *))
*/
int load (void * exec) {
    Function f = NULL;
    Function in = NULL;
    double *n;
    int i = 0;
    double time;
    int numero_executados = 0;
    void (*p_exec)(char *, int, double, int (*)(void *), void *);
    in = exec;
    p_exec = (void (*)(char *, int, double, int (*)(void *),void *)) in->f;
    time = time2();

    for (i = 0; i < size; ++i) {
        if (lista[i] != NULL && lista[i]->to <= time) {
            /* fprintf(stderr, "%d %s\n", i,lista[i]->name); */
            n = malloc2(sizeof(double));
            *n = lista[i]->dt;
            p_exec(lista[i]->name, lista[i]->line, *n, func, (void *)n);
            remaning--;

            lista[i] = NULL;
            numero_executados++;
        }
    }

    if (numero_executados == 0) {
        sleep2(WAIT_TIME);
    }
    if (remaning > 0) {
        f = malloc2(sizeof(struct function));
        f->f = p_exec;
        p_exec("load_process", -1,  WAIT_TIME, load, (void *)f);
    }
    return 0;
}
