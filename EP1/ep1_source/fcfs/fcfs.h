/********************************************************************
 *  Nomes: Gabriel Capella                       Números USP: 8962078 
 *         Luís Felipe de Melo Costa Silva                    9297961
 * 
 *  Arquivo: fcfs.h
 *  Descrição: Implementa as funções exec, init e run usando o 
 *             usando o escalonador FCFS (Fist come first served.)
 ********************************************************************/      

#ifndef FCFS_H
#define FCFS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include "../time2/time2.h"
#include "../collector/collector.h"

/* Adiciona um novo processo à fila de execução */
void fcfs_exec(char *name, int line, double remaining, int (*func) (void *), void *arg);

/* Inicia o escalonador. Precisa ter um processo na fila antes de iniciar */
void fcfs_init(char *log_file, int output);

/* Chamado em tempos em tempos pelo processo */
int fcfs_run();

#endif
