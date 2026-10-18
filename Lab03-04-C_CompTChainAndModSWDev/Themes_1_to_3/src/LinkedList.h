#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdlib.h>
#include <stdio.h>

/*ESTA PARTE DO CODIGO DEVE ESTAR COMENTADA PARA A 3.1 E DESCOMENTADA PARA A
3.2. 
NA 3.1 DEVE ESTAR A DECLARAÇÃO COMPLETA DA STRUCT AQUI! 

typedef struct Node NODE;*/

typedef struct Node {
    int val;               
    struct Node *next;     
} NODE;

NODE* insert(NODE *head, int value);
NODE* delete(NODE *head, int value);
void printList(const NODE *head);

void freeList(NODE *head); 

#endif