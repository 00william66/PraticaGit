#include <stdlib.h>
#include "word_list.h"


typedef struct LinkedList{
    char *word;
    int wordCount;
    struct LinkedList *ptr;
} WORD;     /*para unit testing deve estar comentado*/


/* lembrar que '*' é o caracter de desreferenciação.

**head: Conteúdo do nó em si (a estrutura WORD com word, wordCount e ptr).

*head: Endereço do nó na Heap (o ponteiro que aponta para o nó).

head: Endereço da variável ponteiro que guarda o endereço do nó (ponteiro para o ponteiro)

*/
void newWord(WORD **head, const char *incomingWord) 
{
    WORD *newNode = (WORD *)malloc(sizeof(WORD));
    if(newNode ==NULL){return;} /*return ao nó atual se houver erro de alocação*/

    (*newNode).word = (char *)malloc(strlen(incomingWord)+1);
    if((*newNode).word == NULL)
    {
        free(newNode);
        return;
    }
    strcpy((*newNode).word, incomingWord);

    (*newNode).ptr = *head;
    (*newNode).wordCount = 1;
    *head = newNode;
}


void search(WORD **head, const char *Word)
{
    WORD *current = *head; /* Começa no primeiro nó */

    /* Percorre a lista nó a nó */
    while (current != NULL) {
        if (strcmp((*current).word, Word) == 0) {
            (*current).wordCount++; /* Encontrou, Incrementa e dá return */
            return;
        }
        current = (*current).ptr; /* Avança para o próximo nó */
    }

    /* Se o ciclo terminou (current == NULL), a palavra não existe na lista */
    newWord(head, Word);
}

void freeList(WORD **head) {
    WORD *current = *head;
    WORD *next = NULL;

    while (current != NULL) {
        next = (*current).ptr;     /* Guarda a referência do próximo nó */
        free((*current).word);     /* Liberta a memória da string */
        free(current);           /* Liberta a memória da estrutura do nó */
        current = next;          /* Avança para o próximo */
    }

    *head = NULL;                /* Garante que o ponteiro principal fica limpo */
}

void printList(const WORD *head) {
    const WORD *current = head;
    printf("Word frequency:\n");
    while (current != NULL) {
        printf("- %s: %d\n", (*current).word, (*current).wordCount);
        current = (*current).ptr;
    }
}


void wordFreq(const char *fileName, WORD **head)
{
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Error: Unable to open file '%s'\n", fileName);
        return;
    }

    char buffer[128];

    /* Lê palavra a palavra até ao final do ficheiro (EOF) */
    while (fscanf(file, "%127s", buffer) == 1) {

        search(head, buffer);
    }

    fclose(file);
}