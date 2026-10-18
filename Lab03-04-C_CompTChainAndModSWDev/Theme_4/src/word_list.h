#ifndef WORD_LIST_H
#define WORD_LIST_H

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

typedef struct LinkedList WORD;

/*typedef struct LinkedList {
    char *word;
    int wordCount;
    struct LinkedList *ptr;
} WORD;    para o unit testing deve estar não comentado*/

void newWord(WORD **head, const char *incomingWord);
void search(WORD **head, const char *Word);
void printList(const WORD *head);
void wordFreq(const char *fileName, WORD **head);
void freeList(WORD **head);

#endif