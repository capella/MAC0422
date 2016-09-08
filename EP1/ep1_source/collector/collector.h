/* //////////////////////////////////////////////////////////////
// 
// Autor: Gabriel Capella
// Numero USP: 8962078
// Sigla: GABRIELC
// Data: 2015-10-13
// 
////////////////////////////////////////////////////////////// */
#ifndef COLLECTOR_H
#define COLLECTOR_H

#include <stdlib.h> /* malloc, free, realloc, EXIT_SUCCESS */
#include <stdio.h>

void * malloc2 (int size);
void * realloc2 (void *value, int size);

void free_all ();

#endif
