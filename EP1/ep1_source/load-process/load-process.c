/* //////////////////////////////////////////////////////////////
// 
// Autor: Gabriel Capella
// Numero USP: 8962078
// Sigla: GABRIELC
// Data: 2015-10-13
// 
////////////////////////////////////////////////////////////// */
#include "load-process.h"
#define MAX_PROCESS_SIZE 20

struct p_load {
    float	to;
    char 	* name;
    float   dt;
    float	deadline;
    int 	line;
};
typedef struct p_load * Load;

Load *lista = NULL;
int size, max_size, remaning;

static void * nada (void *duracao) {
	float * duration;
	double init = time2();
	unsigned long soma = 0;
	duration = (float *)duracao;
	while (init + * duration > time2()) {
		soma++;
	}
	free(duracao);
	return NULL;
}

void *load_file (void *filename) {
	FILE *entrada;
	Load novo;
	Load *tmp_lista;
	float tmp_to, tmp_dt, tmp_deadline;
	char *tmp_name;
	char *name;

	name = (char*)filename;
	printf("Carregando arquivo %s\n", name);

	entrada = fopen (name, "r");
	size = 0;
	max_size = 10;

	lista = malloc (sizeof(Load) * max_size);
	tmp_name = malloc (MAX_PROCESS_SIZE * sizeof(char));

	while (1) {
		if (fscanf(entrada, "%f", &tmp_to) == EOF) break;
		if (fscanf(entrada, "%s", tmp_name) == EOF) break;
		if (fscanf(entrada, "%f", &tmp_dt) == EOF) break;
		if (fscanf(entrada, "%f", &tmp_deadline) == EOF) break;

		size++;
		if (size > max_size) {
			max_size *= 2;
			tmp_lista = realloc (lista, max_size * sizeof(Load));
			free (lista);
			lista = tmp_lista;
		}
		novo = malloc(sizeof(struct p_load));
		novo->to = tmp_to;
		novo->dt = tmp_dt;
		novo->deadline = tmp_deadline;
		novo->name = tmp_name;
		novo->line = size-1;
		tmp_name = malloc (MAX_PROCESS_SIZE * sizeof(char));
		lista[size-1] = novo;
	}
	free (tmp_name);
	remaning = size;

	/* printf("Arquivo carregado!\n"); */

	return NULL;
}

/* função que chama, e funcao a ser chamada 
void *(void (*)(char *, int, void *(*)(void*), void *))
*/
void * load (void * exec) {
	float *n;
	int i = 0;
	double time;
	int numero_executados = 0;
	void (*p_exec)(char *, int, void *(*)(void *), void *);
	p_exec = (void (*)(char *, int, void *(*)(void *),void *))exec;
	time = time2();

	for (i = 0; i < size; ++i) {
		if (lista[i] != NULL && lista[i]->to <= time) {
			/* printf("%d %s\n", i,lista[i]->name); */
			n = malloc(sizeof(float));
			*n = lista[i]->dt;

			p_exec(lista[i]->name, lista[i]->line, nada, (void *)n);
			remaning--;

			free (lista[i]);
			lista[i] = NULL;
			numero_executados++;
		}
	}
	if (numero_executados == 0) {
		usleep(500000);
	}
	if (remaning > 0) {
		p_exec("load_process", -1, load, (void *)p_exec);
	}
	return NULL;
}
