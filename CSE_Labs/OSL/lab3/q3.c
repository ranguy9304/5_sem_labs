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
        printf("---CHILD CALLED---\n");
        printf("PID : %d\n",getpid());
        printf("PARENT PID : %d\n",getppid());
        printf("---CHILD END---\n");
        exit(0);
        

       
    }
    else
    { /* parent process */
        /* parent will wait for the child to complete */
        wait(NULL);
        printf("---PARENT CALL--- \n");
        printf("CHILD PID : %d\n",pid);
        printf("PARENT PID : %d\n",getpid());
        printf("---PARENT END---\n");
        exit(0);
    }
}