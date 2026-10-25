#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    pid_t pid = fork();

    if(pid < 0){
        printf("Fo(r)cking error\n");
    } else if(pid == 0){
        printf("\nI'm the child of the grandparent process\n");
        printf("PID: %d, PPID: %d\n", getpid(), getppid());

        fflush(stdout);
        pid_t pid2 = fork();
        if(pid2 < 0){
            printf("Fo(r)cking error\n");
        } else if(pid2 == 0){
            printf("\nI'm the child of the child of the grandparent process\n");
            printf("PID: %d, PPID: %d\n", getpid(), getppid());
        } else {
            wait(NULL);
        }
    } else {
        printf("\nI'm the grandparent process");
        printf("PID: %d\n", getpid());
        printf("I have no parents\n");

        wait(NULL);
    }

    printf("\nProcess PID %d is finishing now\n", getpid());
    return 0;
}