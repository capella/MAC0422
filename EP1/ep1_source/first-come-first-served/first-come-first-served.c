/* //////////////////////////////////////////////////////////////
// 
// Autor: Gabriel Capella
// Numero USP: 8962078
// Sigla: GABRIELC
// Data: 2015-10-13
// 
////////////////////////////////////////////////////////////// */
#include "first-come-first-served.h"

struct process {
    char 			* name;
    int 			line;
    void 			*(*func) (void *);
    void 			* arg;
    struct process 	* next;
};
typedef struct process * Process;

static Process head;
int init = 0;
int running = 0;
pthread_mutex_t head_lock;
/*static n = 1;*/

void fcfs_exec(char *name, int line, void *(*func) (void *), void *arg) {
	Process tmp, novo;


	if (init) pthread_mutex_lock(&head_lock);
	tmp = head;

	if (line >= 0) 
		printf("%.3lf\t       IN '%s' (%d)\n",  time2(), name, line);

	while (tmp != NULL && tmp->next != NULL) tmp = tmp->next;

	novo = malloc(sizeof(struct process));
	novo->name = name;
	novo->line = line;
	novo->func = func;
	novo->arg = arg;
	novo->next = NULL;
	if (head == NULL) head = novo;
	else tmp->next = novo;
	if (init) pthread_mutex_unlock(&head_lock);
}

static void * escalona (void * n) {
	Process atual;
	int *number;
	int flag;

	number = (int *)n;
	while (1) {
		/* tiro ele da fila */
		pthread_mutex_lock(&head_lock);
		if (head != NULL) {
			atual = head;
			head = head->next;
			running++;
			pthread_mutex_unlock(&head_lock);

			if (atual->line >= 0)
				printf("%.3lf\t %3d > START '%s' (%d)\n", time2(), *number, atual->name, atual->line);

			atual->func(atual->arg);


			pthread_mutex_lock(&head_lock);
			running--;
			pthread_mutex_unlock(&head_lock);

			if (atual->line >= 0)
				printf("%.3lf\t %3d > END '%s' (%d)\n", time2(), *number, atual->name, atual->line);

			/*free (atual->name);
			free (atual->arg);
			free (atual);*/
		} else {
			flag = running == 0 && head == NULL;
			pthread_mutex_unlock(&head_lock);
			if (flag) {
					printf("%.3lf\t %3d > OFF\n", time2(), *number);
				return NULL;
			}
			/* usleep(500000); */
			/* sleep(1); */
			usleep(50000);
		}
	}
}

void fcfs_init() {
	pthread_t *threads_ids;
	int i, threads;
	int *cpu_n;
	threads = sysconf(_SC_NPROCESSORS_ONLN);

	threads_ids = malloc(sizeof(pthread_t) * threads);
	cpu_n = malloc(sizeof(int) * threads);
	if (pthread_mutex_init(&head_lock, NULL) != 0) {
		printf("Erro ao criar mutex!\n");
	} else {
		init = 1;
		for (i = 0; i < threads; ++i) {
			cpu_n[i] = i;
			pthread_create(&threads_ids[i], NULL, escalona, &cpu_n[i]);
		}
		for (i = 0; i < threads; ++i) {
			pthread_join(threads_ids[i], NULL);
		}
		pthread_mutex_destroy(&head_lock);
	}
}

/* chamado em tempos em tesmpos pelo processo */
void fcfs_run() {

}

