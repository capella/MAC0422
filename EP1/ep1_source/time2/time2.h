/********************************************************************
 *  Nomes: Gabriel Capella                       Números USP: 8962078 
 *         Luís Felipe de Melo Costa Silva                    9297961
 * 
 *  Arquivo:   time2.h
 *  Descrição: Biblioteca que implementam funções de relógio.
 ********************************************************************/   
#ifndef TIME2_H
#define TIME2_H

#define _POSIX_C_SOURCE	199309L

#include <stdio.h>
#include <sys/time.h>
#include <time.h>

/* Devolve o tempo do sistema em formato double. Na primeira vez em
   que é usada ela configura o zero. */
double time2 ();

/* Faz o processo "dormir" por uma quantidade sec de segundos. */
void sleep2 (double sec);

#endif
