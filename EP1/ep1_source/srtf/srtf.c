/* //////////////////////////////////////////////////////////////
// 
// Autor: Gabriel Capella
// Numero USP: 8962078
// Sigla: GABRIELC
// Data: 2015-10-13
// 
////////////////////////////////////////////////////////////// */
#include "srtf.h"
#define ALL 63
#define DEF 64

struct process_strf {
    char            * name;
    int             line;
    int             (*func) (void *);
    float           remaining;
    float           original;
    void            * arg;
    double          init;  
    struct process_strf     * next;
};
typedef struct process_strf * ProcessSTRF;

static ProcessSTRF head;
static int init = 0;
static int running = 0;
static pthread_mutex_t head_lock;
static pthread_mutex_t file_lock;
static int *notify;
static pthread_t *threads_ids;
static long threads;

static int maior_em_exec;
static double maior_em_exec_end;

static FILE *log;
static int context_changes;

static int output_info;

void srtf_exec(char *name, int line, double remaining, int (*func) (void *), void *arg) {
    ProcessSTRF p, q, novo;

    if (init) pthread_mutex_lock(&head_lock);

    fprintf(stderr, "%.3f\t       NEW '%s' (%d)\n",  time2(), name, line);

    novo = malloc(sizeof(struct process_strf));
    novo->name = name;
    novo->line = line;
    novo->func = func;
    novo->remaining = remaining;
    novo->original = remaining;
    novo->arg = arg;
    novo->next = NULL;
    novo->init = time2();

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

    if (init) {
        /* retira um processo se ele demorar menos que algum e não tiver cpu livres */
        if (running == threads && novo->remaining+time2() < maior_em_exec) {
            notify[maior_em_exec] = 1;
        }
    }

    if (init) pthread_mutex_unlock(&head_lock);
}

static void * escalona (void * n) {
    ProcessSTRF atual, p, q;
    int *number;
    int flag;
    double start;
    int return_value;
    double tf;

    number = (int *)n;
    while (1) {
        /* tira ele da fila */
        pthread_mutex_lock(&head_lock);
        if (head != NULL) {
            atual = head;
            head = head->next;
            running++;
            if (maior_em_exec_end < time2()+atual->remaining) {
                maior_em_exec = *number;
                maior_em_exec_end = time2()+atual->remaining;
            }
            pthread_mutex_unlock(&head_lock);

            if (atual->line >= 0 || 1) {
                if (atual->remaining == atual->original) {
                    fprintf(stderr, "%.3f\t %3d > START '%s' (%d)\n", time2(), *number, atual->name, atual->line);
                } else {
                    fprintf(stderr, "%.3f\t %3d > IN '%s' (%d)\n", time2(), *number, atual->name, atual->line);
                }
            }

            start = time2();
            return_value = atual->func(atual->arg);

            pthread_mutex_lock(&head_lock);
            atual->remaining -= time2()-start;
            /* adiciona processo novamente na fila */
            if (return_value == 1) {
                fprintf(stderr, "%.3f\t %3d > OUT '%s' (%d) F: %f\n", time2(), *number, atual->name, atual->line,atual->remaining);
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
                } else  { 
                    head = atual;
                }
                context_changes++;
            } else {
                if (atual->line >= 0) {
                    tf = time2();
                    pthread_mutex_lock(&file_lock);
                    fprintf(log, "%s %.5f %.5f\n", atual->name, tf, tf - atual->init);
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

void srtf_init(char *log_file, int output) {
    int i;
    int *cpu_n;
    threads = sysconf(_SC_NPROCESSORS_ONLN);
    log = fopen(log_file, "w");

    threads_ids = malloc(sizeof(pthread_t) * threads);
    cpu_n = malloc(sizeof(int) * threads);
    notify = malloc(sizeof(int) * threads);
    context_changes = 0;

    if (pthread_mutex_init(&head_lock, NULL) != 0 &&
        pthread_mutex_init(&file_lock, NULL) != 0) {
        fprintf(stderr, "Erro ao criar mutex!\n");
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
        pthread_mutex_destroy(&file_lock);
    }
    fprintf(log, "%d\n", context_changes);
    fclose(log);
}

/* chamado em tempos em tempos pelo processo */
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
