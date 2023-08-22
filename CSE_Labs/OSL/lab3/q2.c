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
        printf("loading binary\n");
        char *args[]={"./q1",NULL};
        execv(args[0],args);
        exit(0);
    }
    else
    { /* parent process */
        /* parent will wait for the child to complete */
        wait(&stats);
        printf("Complete %d\n",stats);
        exit(0);
    }
}