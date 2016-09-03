/* //////////////////////////////////////////////////////////////
// 
// Autor: Gabriel Capella
// Numero USP: 8962078
// Sigla: GABRIELC
// Data: 2015-10-13
// 
////////////////////////////////////////////////////////////// */
#include "srtf.h"

struct process_strf {
    char 			* name;
    int 			line;
    void 			*(*func) (void *);
    float 			remaining;
    float 			original;
    void 			* arg;
    struct process_strf 	* next;
};
typedef struct process_strf * ProcessSTRF;

static ProcessSTRF head;
static int init = 0;
static int running = 0;
static pthread_mutex_t head_lock;
static int *notify;
static pthread_t *threads_ids;
static int threads;
/*static n = 1;*/

void srtf_exec(char *name, int line, double remaining, void *(*func) (void *), void *arg) {
	ProcessSTRF p, q, novo;
	pthread_t my_id;
	int i;

	my_id = pthread_self();

	if (init) pthread_mutex_lock(&head_lock);

	/* if (line >= 0 || 1) */
		printf("%.3lf\t       NEW '%s' (%d)\n",  time2(), name, line);

	novo = malloc(sizeof(struct process_strf));
	novo->name = name;
	novo->line = line;
	novo->func = func;
	novo->remaining = remaining;
	novo->original = remaining;
	novo->arg = arg;
	novo->next = NULL;

	if (head == NULL || head->remaining > remaining) {
		novo->next = head;
		head = novo;
	} else  {
		p = head;
		q = head->next;
		while (q != NULL && q->remaining > remaining) {
			p = q;
			q = q->next;
		}
	   novo->next = q;
	   p->next = novo;
	}

	for (i = 0; i < threads; ++i) {
		if (my_id != threads_ids[i]) {
			notify[i] = 1;
		}
	}

	p = head;
	while (p != NULL) {
		printf(">%s %lf\n", p->name, p->remaining);
		p = p->next;
	}

	if (init) pthread_mutex_unlock(&head_lock);
}

static void * escalona (void * n) {
	ProcessSTRF atual, p, q;
	int *number;
	int flag;
	double start;

	number = (int *)n;
	while (1) {
		/* tiro ele da fila */
		pthread_mutex_lock(&head_lock);
		if (head != NULL) {
			atual = head;
			head = head->next;
			running++;
			pthread_mutex_unlock(&head_lock);

			if (atual->line >= 0 || 1) {
				if (atual->remaining == atual->original) {
					printf("%.3lf\t %3d > START '%s' (%d)\n", time2(), *number, atual->name, atual->line);
				} else {
					printf("%.3lf\t %3d > IN '%s' (%d)\n", time2(), *number, atual->name, atual->line);
				}
			}

			start = time2();
			atual->func(atual->arg);

			pthread_mutex_lock(&head_lock);
			atual->remaining -= time2()-start;
			/* adiciona processo novamente na fila */
			if (atual->remaining > 0 && atual->line >= 0) {
				printf("%.3lf\t %3d > OUT '%s' (%d)\n", time2(), *number, atual->name, atual->line);
				atual->next = NULL;
				if (head != NULL) {
					p = head;
					q = head->next;
					while (q != NULL && q->remaining > atual->remaining) {
						p = q;
						q = q->next;
					}
				   atual->next = q;
				   p->next = atual;
				} else  head = atual;
			} else if (atual->line >= 0)
				printf("%.3lf\t %3d > END '%s' (%d)\n", time2(), *number, atual->name, atual->line);
			running--;
			pthread_mutex_unlock(&head_lock);


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

void srtf_init() {
	int i;
	int *cpu_n;
	threads = sysconf(_SC_NPROCESSORS_ONLN);

	threads_ids = malloc(sizeof(pthread_t) * threads);
	cpu_n = malloc(sizeof(int) * threads);
	notify = malloc(sizeof(int) * threads);
	if (pthread_mutex_init(&head_lock, NULL) != 0) {
		printf("Erro ao criar mutex!\n");
	} else {
		init = 1;
		for (i = 0; i < threads; ++i) {
			cpu_n[i] = i;
			notify[i] = 0;
			pthread_create(&threads_ids[i], NULL, escalona, &cpu_n[i]);
		}
		for (i = 0; i < threads; ++i) {
			pthread_join(threads_ids[i], NULL);
		}
		pthread_mutex_destroy(&head_lock);
	}
}

/* chamado em tempos em tesmpos pelo processo */
int srtf_run() {
	int i;
	pthread_t my_id;
	my_id = pthread_self();
	for (i = 0; i < threads; ++i) {
		if (my_id == threads_ids[i]) {
			if (notify[i] == 1){
				notify[i] = 0;
				return 1;
			}
		}
	}
	return 0;
}

