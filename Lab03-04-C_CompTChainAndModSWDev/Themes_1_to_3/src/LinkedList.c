#include "LinkedList.h"

/*
typedef struct Node {
    int val;               
    struct Node *next;     
} NODE;

ESTA DECLARAÇÃO DA ESTRUTURA DEVE ESTAR COMENTADA
PARA A 3.1, PARA A 3.2 DEVE ESTAR DESCOMENTADA*/ 


NODE* insert(NODE *head, int value)
{
    /*Criar novo nó na heap*/
    NODE *newNode = (NODE *)malloc(sizeof(NODE));
    
    if(newNode == NULL){
        return head;    /*dá return ao nó presente se houver erro de 
alocação de espaço*/
    }

    newNode->val = value;
    newNode->next = head; /* Funciona mesmo se head for NULL!
    que é o caso no primeiro nó que se inserir*/

    return newNode; /*devolve o ponteiro para o novo nó como nova head*/
}

NODE* delete(NODE *head, int value)
{
    NODE *search = head;
    NODE *temp;

    if(head == NULL){
        return NULL;
    }

    if (head->val == value) {
        NODE *temp = head;
        head = head->next;
        free(temp);
        return head;

    } else {
        while(search->next != NULL){
            if(search->next->val == value){
                temp = search->next;
                search->next = search->next->next;
                free(temp);
            break;
            }
            search = search->next;
        }
    }
    return head;
}



void printList(const NODE *head)
{
    const NODE *current = head;

    if(current == NULL){
        printf("Empty list.\n");
        return;
    }

    printf("List: ");
    
    while(current != NULL){
        printf("%d -> ", current->val);
        current = current->next;
    }
    printf("NULL\n");
}


void freeList(NODE *head)
{
    NODE *current = head;
    while (current != NULL) {
        NODE *temp = current;
        current = current->next;
        free(temp);
    }
}