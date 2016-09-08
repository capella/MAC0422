/********************************************************************
 *  Nomes: Gabriel Capella                       Números USP: 8962078 
 *         Luís Felipe de Melo Costa Silva                    9297961
 * 
 *  Arquivo:   collector.h
 *  Descrição: Funções que implementam a coleta de memória alocada 
 *             durante a execução do programa.
 ********************************************************************/   

#ifndef COLLECTOR_H
#define COLLECTOR_H

#include <stdlib.h> /* malloc, free, realloc, EXIT_SUCCESS */
#include <stdio.h>

/* Aloca memória para um ponteiro, a partir de um tamanho recebido.*/
void * malloc2 (int size);

/* Realoca memória para um ponteiro. */
void * realloc2 (void *value, int size);

/* Libera todos os espaços de memória usados durante a execução do 
   programa. */
void free_all ();

#endif
