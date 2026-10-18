#include "file_utils.h"

void countParam(const char *fileName, int *numLines, int *numWords, int *numChar)
{
    FILE *file;
    int ch; /* Tem de ser int para detetar o EOF corretamente */
    int characters = 0, words = 0, lines = 0;
    
    /* Variável de estado para detetar limites de palavras */
    int inWord = 0; /* 0 = fora de uma palavra, 1 = dentro de uma palavra */
    
    file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Error: Unable to open file '%s'\n", fileName);
        return; /* Se der erro, aborta a função para não dar crash */
    }

    while ((ch = fgetc(file)) != EOF) {
        /* 1. Contar caracteres (incluindo espaços) */
        characters++;

        /* 2. Contar linhas */
        if (ch == '\n') {
            lines++;
        }

        /* 3. Contar palavras */
        if (ch == ' ' || ch == '\n' || ch == '\t' || ch == '\r') {
            /* Se for espaço, enter ou tab, saímos da palavra */
            inWord = 0;
        } else if (inWord == 0) {
            /* Se for uma letra e estava FORA de uma palavra, é uma palavra nova */
            inWord = 1;
            words++;
        }
    }

    fclose(file);

    if (numLines != NULL) *numLines = lines;
    if (numWords != NULL) *numWords = words;
    if (numChar != NULL)  *numChar = characters;
}

