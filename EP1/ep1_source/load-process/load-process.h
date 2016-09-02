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
#include <unistd.h>
#include "../time2/time2.h"

void *load_file (void *filename);

/* Le o arquivos com os processos (se nunca foi lido);
   Verifica o tempo de inicio dos processos e inicia sua execução caso seja a hora;
   Coloca ela mesmo na fila de processos; 
   void (*exec)(void) função do escalonador que cria os processos;
   void (*p) processo a ser criado */
void * load (void * exec);

#endif
/* http://stackoverflow.com/questions/1789807/function-pointer-as-an-argument */
