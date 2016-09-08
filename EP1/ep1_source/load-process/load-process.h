/********************************************************************
 *  Nomes: Gabriel Capella                       Números USP: 8962078 
 *         Luís Felipe de Melo Costa Silva                    9297961
 * 
 *  Arquivo:   load-process.h
 *  Descrição: Biblioteca para carregamento de processos.
 ********************************************************************/      

#ifndef LOAD_H
#define LOAD_H

#include <stdlib.h> /* malloc2, free, realloc2, EXIT_SUCCESS */
#include <stdio.h>  /* EOF, printf, getchar */
#include "../time2/time2.h"
#include "../collector/collector.h"

#define WAIT_TIME 0.05 /* segundos */

struct function {
    void (*f)();
};
typedef struct function * Function;

/* Pega as informações do processo do arquivo de entrada, e coloca em
    um vetor de ponteiros para struct de processos. */
void load_file (void *filename, int (*) (void *));

/* Lê o arquivos com os processos (se nunca foi lido);
    Verifica o tempo de início dos processos e inicia sua execução caso
    seja a hora;
    Coloca ela mesma na fila de processos; 
    void (*exec)(void) função do escalonador que cria os processos;
    void (*p) processo a ser criado */
int load (void * exec);

#endif
/* http://stackoverflow.com/questions/1789807/function-pointer-as-an-argument */
