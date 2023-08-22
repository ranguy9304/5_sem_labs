#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include<stdlib.h>
int main()

{
    int stats;
    pid_t pid;
    /* fork another process */
    pid = fork();
    if (pid < 0)
    { /* error occurred */
        fprintf(stderr, "Fork Failed");
        exit(-1);
    }
    else if (pid == 0)
    { /* child process */
        printf("child first\n");
        for(int i=0;i<3;i++){
            sleep(1);
            printf("waiting ...\n");
        }
        exit(0);
    }
    else
    { /* parent process */
        /* parent will wait for the child to complete */
        wait(&stats);
        printf("Child Complete %d\n",stats);
        exit(0);
    }
}