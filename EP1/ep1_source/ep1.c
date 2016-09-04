#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "load-process/load-process.h"
#include "fcfs/fcfs.h"
#include "srtf/srtf.h"
#include "mufi/mufi.h"

void (*p_init)();
int (*p_run)(int);
void (*p_exec)(char *, int, double, int (*)(void *), void *);

int nada (void *duracao);

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
            p_init = &mufi_init;
            p_run = &mufi_run;
            p_exec = &mufi_exec;
            break;
    }

    load_file((void *)argv[2], nada);
    p_exec("load_process", -1, 0, load, (void *)p_exec);

    p_init(argv[3]);

    return 0;
}

int nada (void *duracao) {
    double * duration;
    double init = time2();
    unsigned long soma = 0;
    duration = (double *)duracao;
    /* printf("%lf\n", *duration); */
    while (init + * duration > time2()) {
        soma++;

        /* pergunta para o escalonador se pode continuar rodando */
        if (p_run(0)) {
            * duration = * duration - time2() + init;
            /* retorna 1 para sinalizar que o processo deve ser interompido */
            return 1;
        }
    }
    /* processo finalizado */
    return 0;
}
