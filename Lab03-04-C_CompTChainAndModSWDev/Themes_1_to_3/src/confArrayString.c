#include "confArrayString.h"
#include "gen_rand.h"

int* generateArrayStats(int n, int m, float *avg, int *min, int *max)
{
    int *array = NULL;
    int sum = 0;
    int val, randGenCount;
    int i;

    /* Validação defensiva de parâmetros */
    if (n <= 0 || m <= 0 || avg == NULL || max == NULL || min == NULL) {
        return NULL;
    }

    /* Alocação dinâmica de memória na Heap */
    array = (int *)malloc(n * sizeof(int));
    if (array == NULL) {
        return NULL; /* Falha do malloc */
    }

    /* Inicialização do array com valores random */
    for (i = 0; i < n; i++) {
        RandFunc(&val, &randGenCount);

        /* Garante que o valor fica estritamente no intervalo [1, M] */
        array[i] = (val % m) + 1;
        sum += array[i];

        /* Determinação do Mínimo e Máximo */
        if (i == 0) {
            *max = array[i];
            *min = array[i];
        } else {
            if (array[i] > *max){
                *max = array[i];
            } 
            
            if (array[i] < *min){
                *min = array[i];
            } 
            
        }
    }

    /* Média */
    *avg = (float)sum / n;

    /*Devolve o ponteiro para o array alocado */
    return array;
}


void swapInt(int *p1, int *p2)
{
    int temp;
    
    if(p1 == NULL ||p2 == NULL){

       return;
    }   

    temp = *p1;
    *p1 = *p2;
    *p2 = temp;

}

int strLength(char *s)
{
    int i = 0;
    for(i = 0; s[i] != '\0'; i++);
    return i;
}


void stringRev(char *Str)
{
    char *p1, *p2, aux;
    
    if(Str == NULL){
        return;
    }

    p1 = Str; /*aponta para Str[0]*/
    p2 = Str + strLength(Str) - 1; /*Aponta para o ultimo elemento*/

    while(p1 < p2){
        aux = *p1;
        *p1 = *p2;
        *p2 = aux;

        p1++;
        p2--;
    }

}
