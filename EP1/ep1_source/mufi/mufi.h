/********************************************************************
 *  Nomes: Gabriel Capella                       Números USP: 8962078 
 *         Luís Felipe de Melo Costa Silva                    9297961
 * 
 *  Arquivo:   mufi.h
 *  Descrição: Biblioteca de funções que usam o escalonador de 
               múltiplas filas.
 ********************************************************************/      

#ifndef MUFI_H
#define MUFI_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include "../time2/time2.h"
#include "../collector/collector.h"

/* Adiciona um novo processo a fila de execução */
void mufi_exec(char *name, int line, double remaining, int (*func) (void *), void *arg);

/* Inicia o escalonador. Precisa ter um processo na fila antes de iniciar */
void mufi_init(char *log_file, int output);

/* Chamado em tempos em tempos pelo processo */
int mufi_run();

#endif
