#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "load-process/load-process.h"
#include "fcfs/fcfs.h"
#include "srtf/srtf.h"

void (*p_init)();
int (*p_run)(int);
void (*p_exec)(char *, int, double, void *(*)(void *), void *);

void * nada (void *duracao);

int main(int argc, char const *argv[]) {
    int tipo;

    sscanf (argv[1],"%d",&tipo);

    switch(tipo) {
        case 1:
            p_init = &fcfs_init;
            p_run = &fcfs_run;
            p_exec = &fcfs_exec;
            break; 
        
        case 2:
            p_init = &srtf_init;
            p_run = &srtf_run;
            p_exec = &srtf_exec;
            break;

        case 3:
            p_init = &fcfs_init;
            p_run = &fcfs_run;
            p_exec = &fcfs_exec;
            break;
    }

    load_file((void *)argv[2], nada);
    p_exec("load_process", -1, 0, load, (void *)p_exec);

    p_init();

    return 0;
}

void * nada (void *duracao) {
    double * duration;
    double init = time2();
    unsigned long soma = 0;
    duration = (double *)duracao;
    /* printf("%lf\n", *duration); */
    while (init + * duration > time2()) {
        soma++;
        if (p_run(0)) {
            * duration = * duration - time2() + init;
            break;
        }
    }
    return NULL;
}
