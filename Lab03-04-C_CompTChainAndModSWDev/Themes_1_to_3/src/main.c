#include "configData.h"
#include "gen_rand.h"
#include "confArrayString.h"
#include "LinkedList.h"
#include <time.h>
#include <stdio.h>


int main(void)
{
puts("----------   THEME 1   ----------");
    ConfigInit();
    printf("maxConnections 1 = %u\n", configGetMaxConnections());
    configSetMaxConnections(45);
    printf("maxConnections 1 = %u\n", configGetMaxConnections());
    ConfigInit();
    printf("maxConnections 3 = %u\n\n", configGetMaxConnections());


puts("----------   THEME 2   ----------");
puts("      -------   2.1   -------\n");        
    int *arrayVar, min, max, i;
    int m = 100;
    int n = 10;
    float average;
    
    srand((unsigned int)time(NULL));

    arrayVar = generateArrayStats(n, m, &average, &min, &max);

    if(arrayVar != NULL){
        printf("Array gerado: ");
        for(i = 0; i < n; i++){
            printf("%d", arrayVar[i]);
            printf(" ");
        }
        printf("\n");

        printf("Média: %.2f\n", average);
        printf("Mínimo: %d\n", min);
        printf("Máximo: %d\n\n", max);

puts("      -------   2.2   -------");        
        int ind1 = 1;
        int ind2 = 4;

        if (ind1 >= 0 && ind1 < n && ind2 >= 0 && ind2 < n) {
            swapInt(&arrayVar[ind1], &arrayVar[ind2]);
        } else {
            printf("Índices inválidos para troca.\n");
        }

        printf("Array após troca: ");
        for(i = 0; i < n; i++){
            printf("%d", arrayVar[i]);
            printf(" ");
        }
        printf("\n\n");

        free(arrayVar);
        arrayVar = NULL;


    } else{
        printf("Erro na alocação de memória ou é o código :0\n\n");
    }

puts("      -------   2.3   -------");
    char string[] = "Esta a funcionar";
    puts(string); /*Equivalente a printf("...\n")*/
    
    stringRev(string);
    puts(string);


puts("\n----------   THEME 3   ----------");
puts("      -------   3.1   -------");
    NODE *movingHead = NULL; /*Declara ponteiro que guarda o endereço de 
    memória de uma variável tipo NODE. Declara que esse ponteiro 
    não aponta para nenhum endereço de memória, está vazio*/
    movingHead = insert(movingHead, 9);
    movingHead = insert(movingHead, 10);
    movingHead = insert(movingHead, 11);
    movingHead = insert(movingHead, 12);
    movingHead = insert(movingHead, 13);
    printList(movingHead);
    movingHead = delete(movingHead, 12);
    printList(movingHead);
    movingHead = delete(movingHead, 9);
    printList(movingHead);

    return 0;
}