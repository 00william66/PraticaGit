#ifndef CONFARRAYSTRING_H
#define CONFARRAYSTRING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 *  Aloca e preenche um array dinâmico com N inteiros entre 1 e M.
 *  n Tamanho do array.
 *  m Valor máximo de cada elemento.
 *  avg Ponteiro de saída para a média dos elementos.
 *  max Ponteiro de saída para o valor máximo.
 *  min Ponteiro de saída para o valor mínimo.
 *  int* Ponteiro para o array alocado no heap (ou NULL em caso de erro).
 */
int* generateArrayStats(int n, int m, float *avg, int *max, int *min);
void swapInt(int *p1, int *p2); 
void stringRev(char *Str);
int strLength(char *s);


#endif