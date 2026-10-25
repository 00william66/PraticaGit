#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(void){
    execlp("ls", "ls", NULL);
    perror("Error while executing ls");
    return 1;
}
