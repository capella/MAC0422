/* //////////////////////////////////////////////////////////////
// 
// Autor: Gabriel Capella
// Numero USP: 8962078
// Sigla: GABRIELC
// Data: 2015-10-13
// 
////////////////////////////////////////////////////////////// */
#ifndef FCFS_H
#define FCFS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "../time2/time2.h"

/* Adiciona um novo processo a fila de execucao */
void fcfs_exec(char *name, int line, double remaining, int (*func) (void *), void *arg);

/* Inicia o escalonador. precisa ter um processo na fila antes de iniciar */
void fcfs_init();

/* chamado em tempos em tesmpos pelo processo */
int fcfs_run();

#endif
