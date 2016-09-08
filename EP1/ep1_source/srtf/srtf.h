/********************************************************************
 *  Nomes: Gabriel Capella                       Números USP: 8962078 
 *         Luís Felipe de Melo Costa Silva                    9297961
 * 
 *  Arquivo:   srtf.c
 *  Descrição: Biblioteca de funções que usam o escalonador SRTN 
 *             (Shortest Remaining Time Next).
 ********************************************************************/  

#define SRTF_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include "../time2/time2.h"
#include "../collector/collector.h"

/* Adiciona um novo processo a fila de execucao */
void srtf_exec(char *name, int line, double remaining, int (*func) (void *), void *arg);

/* Inicia o escalonador. precisa ter um processo na fila antes de iniciar */
void srtf_init(char *log_file, int output);

/* chamado em tempos em tesmpos pelo processo */
int srtf_run();

#endif
