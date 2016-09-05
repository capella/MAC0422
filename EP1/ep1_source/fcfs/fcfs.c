/* //////////////////////////////////////////////////////////////
// 
// Autor: Gabriel Capella
// Numero USP: 8962078
// Sigla: GABRIELC
// Data: 2015-10-13
// 
////////////////////////////////////////////////////////////// */
#include "fcfs.h"
#define ALL 63
#define DEF 64

struct process_fcgs {
    char            * name;
    int             line;
    int             (*func) (void *);
    void            * arg;
    double          init;
    struct process_fcgs     * next;
};
typedef struct process_fcgs * ProcessFCFS;

static ProcessFCFS head;
static int init = 0;
static int running = 0;
static pthread_mutex_t head_lock;
static pthread_mutex_t file_lock;
static FILE *log;

static int output_info;

void fcfs_exec(char *name, int line, double remaining, int (*func) (void *), void *arg) {
    ProcessFCFS tmp, novo;


    if (init) pthread_mutex_lock(&head_lock);
    tmp = head;

    if (line >= 0) 
        fprintf(stderr, "%.3f\t       IN '%s' (%d)\n",  time2(), name, line);

    while (tmp != NULL && tmp->next != NULL) tmp = tmp->next;

    novo = malloc(sizeof(struct process_fcgs));
    novo->name = name;
    novo->line = line;
    novo->func = func;
    novo->arg = arg;
    novo->next = NULL;
    novo->init = time2();

    if (head == NULL) head = novo;
    else tmp->next = novo;
    if (init) pthread_mutex_unlock(&head_lock);
}

static void * escalona (void * n) {
    ProcessFCFS atual;
    int *number;
    int flag;
    double tf;

    number = (int *)n;
    while (1) {
        /* tiro ele da fila */
        pthread_mutex_lock(&head_lock);
        if (head != NULL) {
            atual = head;
            head = head->next;
            running++;
            pthread_mutex_unlock(&head_lock);

            fprintf(stderr, "%.3f\t %3d > START '%s' (%d)\n", time2(), *number, atual->name, atual->line);

            atual->func(atual->arg);

            pthread_mutex_lock(&head_lock);
            running--;
            pthread_mutex_unlock(&head_lock);

            if (atual->line >= 0) {
                tf = time2();
                pthread_mutex_lock(&file_lock);
                fprintf(log, "%s %.5f %.5f\n", atual->name, tf, tf-atual->init);
                pthread_mutex_unlock(&file_lock);
            }
            fprintf(stderr, "%.3f\t %3d > END '%s' (%d)\n", time2(), *number, atual->name, atual->line);


            /*free (atual->name);
            free (atual->arg);
            free (atual);*/
        } else {
            flag = running == 0 && head == NULL;
            pthread_mutex_unlock(&head_lock);
            if (flag) {
                    fprintf(stderr, "%.3f\t %3d > OFF\n", time2(), *number);
                return NULL;
            }
            /* usleep(500000); */
            /* sleep(1); */
            sleep2 (0.05);
        }
    }
}

void fcfs_init(char *log_file, int output) {
    pthread_t *threads_ids;
    int i, threads;
    int *cpu_n;
    threads = sysconf(_SC_NPROCESSORS_ONLN);
    log = fopen(log_file, "w");

    threads_ids = malloc(sizeof(pthread_t) * threads);
    cpu_n = malloc(sizeof(int) * threads);
    if (pthread_mutex_init(&head_lock, NULL) != 0 &&
        pthread_mutex_init(&file_lock, NULL) != 0) {
        fprintf(stderr, "Erro ao criar mutex!\n");
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
        pthread_mutex_destroy(&file_lock);
    }
    fprintf(log, "0\n");
    fclose(log);
}

/* chamado em tempos em tesmpos pelo processo */
int fcfs_run() {
    return 0;
}

