/* //////////////////////////////////////////////////////////////
// 
// Autor: Gabriel Capella
// Numero USP: 8962078
// Sigla: GABRIELC
// Data: 2015-10-13
// 
////////////////////////////////////////////////////////////// */
#include "mufi.h"
#define ALL 63
#define DEF 64

struct process_mufi {
    char            * name;
    int             line;
    int             (*func) (void *);
    void            * arg;
    int             priority;
    int             started; /* marca se já foi iniciado */
    double          init;
    struct process_mufi     * next;
};
typedef struct process_mufi * ProcessMUFI;

static ProcessMUFI head;
static int init = 0;
static int running = 0;
static pthread_mutex_t head_lock;
static pthread_mutex_t file_lock;
static pthread_t *threads_ids;
static long threads;
static double *end_time;

static FILE *log;
static int context_changes;

static int output_info;

void mufi_exec(char *name, int line, double remaining, int (*func) (void *), void *arg) {
    ProcessMUFI tmp, novo;

    if (init) pthread_mutex_lock(&head_lock);
    tmp = head;

    if (line >= 0) 
        fprintf(stderr, "%.3f\t       IN '%s' (%d)\n",  time2(), name, line);

    while (tmp != NULL && tmp->next != NULL) tmp = tmp->next;

    novo = malloc(sizeof(struct process_mufi));
    novo->name = name;
    novo->line = line;
    novo->func = func;
    novo->arg = arg;
    novo->next = NULL;
    novo->priority = 1;
    novo->started = 0;
    novo->init = time2();

    if (head == NULL) head = novo;
    else tmp->next = novo;
    if (init) pthread_mutex_unlock(&head_lock);
}

static void * escalona (void * n) {
    ProcessMUFI atual, tmp;
    int *number;
    int flag;
    int return_value;
    double tf;

    number = (int *)n;
    while (1) {
        /* tiro ele da fila */
        pthread_mutex_lock(&head_lock);
        if (head != NULL) {
            atual = head;
            head = head->next;
            running++;
            end_time[*number] = time2() + atual->priority * QUANTON;
            pthread_mutex_unlock(&head_lock);

            if (atual->started == 0) {
                atual->started = 1;
                fprintf(stderr, "%.3f\t %3d > START '%s' (%d)\n", time2(), *number, atual->name, atual->line);
            } else {
                fprintf(stderr, "%.3f\t %3d > IN '%s' (%d)\n", time2(), *number, atual->name, atual->line);
            }


            return_value = atual->func(atual->arg);

            pthread_mutex_lock(&head_lock);
            if (return_value == 1) {
                fprintf(stderr, "%.3f\t %3d > OUT '%s' (%d)\n", time2(), *number, atual->name, atual->line);
                tmp = head;
                atual->next = NULL;
                atual->priority += 1;
                while (tmp != NULL && tmp->next != NULL) tmp = tmp->next;
                if (head == NULL) head = atual;
                else tmp->next = atual;
                context_changes++;
            } else {
                if (atual->line >= 0) {
                    tf = time2();
                    pthread_mutex_lock(&file_lock);
                    fprintf(log, "%s %.5f %.5f\n", atual->name, tf, tf-atual->init);
                    pthread_mutex_unlock(&file_lock);
                }
                fprintf(stderr, "%.3f\t %3d > END '%s' (%d)\n", time2(), *number, atual->name, atual->line);
            }
            running--;
            pthread_mutex_unlock(&head_lock);
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


void mufi_init(char *log_file, int output) {
    int i;
    int *cpu_n;
    threads = sysconf(_SC_NPROCESSORS_ONLN);
    log = fopen(log_file, "w");
    output_info = output;

    threads_ids = malloc(sizeof(pthread_t) * threads);
    cpu_n = malloc(sizeof(int) * threads);
    end_time = malloc(sizeof(double) * threads);
    context_changes = 0;

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
    fprintf(log, "%d\n", context_changes);
    fclose(log);
}

/* chamado em tempos em tesmpos pelo processo */
int mufi_run() {
    int i;
    pthread_t my_id;
    my_id = pthread_self();
    for (i = 0; i < threads; ++i) {
        if (my_id == threads_ids[i]) {
            /* fprintf(stderr, "%d > %lf - %lf\n", i, end_time[i], time2()); */
            if (end_time[i] <= time2() && running == threads) return 1;
        }
    }
    return 0;
}
