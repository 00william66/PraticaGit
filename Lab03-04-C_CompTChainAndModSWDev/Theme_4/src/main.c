#include <stdio.h>
#include "file_utils.h"
#include "word_list.h"

int main(void) {
    int lines = 0, words = 0, chars = 0;
    WORD *head = NULL; /* Lista inicia vazia */
    const char *filename = "file.txt";

    /* Estatísticas */
    countParam(filename, &lines, &words, &chars);

    /* Frequência das palavras */
    wordFreq(filename, &head);
   
    printf("%d lines\n", lines);
    printf("%d words\n", words);
    printf("%d characters\n", chars);
    
    printList(head);

    freeList(&head);

    return 0;
}