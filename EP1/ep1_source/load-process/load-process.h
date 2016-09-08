/* //////////////////////////////////////////////////////////////
// 
// Autor: Gabriel Capella
// Numero USP: 8962078
// Sigla: GABRIELC
// Data: 2015-10-13
// 
////////////////////////////////////////////////////////////// */
#ifndef LOAD_H
#define LOAD_H

#include <stdlib.h> /* malloc, free, realloc, EXIT_SUCCESS */
#include <stdio.h>  /* EOF, printf, getchar */
#include "../time2/time2.h"

#define WAIT_TIME 0.05 /* segundos */

struct function {
	void (*)() f;
};
typedef struct function * Function;

void load_file (void *filename, int (*) (void *));

/* Le o arquivos com os processos (se nunca foi lido);
   Verifica o tempo de inicio dos processos e inicia sua execução caso seja a hora;
   Coloca ela mesmo na fila de processos; 
   void (*exec)(void) função do escalonador que cria os processos;
   void (*p) processo a ser criado */
int load (void * exec);

#endif
/* http://stackoverflow.com/questions/1789807/function-pointer-as-an-argument */
