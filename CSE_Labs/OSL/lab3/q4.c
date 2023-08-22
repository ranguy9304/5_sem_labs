#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include<stdlib.h>
int main()

{
    int stats;
    pid_t pid;
    /* fork another process */
    // printf("INIT PID? %d\n",getpid());
    pid = fork();
    if (pid < 0)
    { /* error occurred */
        fprintf(stderr, "Fork Failed");
        exit(-1);
    }
    else if (pid == 0)
    { /* child process */
        
        printf("CHILD \tPID : %d\n",getpid());
        printf("PARENT \tPID : %d\n",getppid());
        for(int i =0;i<5;i++){
            sleep(1);
            printf("cild waiting ... \n");
        }
        printf("PARENT \tPID : %d\n",getppid());

        exit(0);
        

       
    }
    else
    { /* parent process */
        /* parent will wait for the child to complete */
        // wait(NULL);

        execl("/bin/ps","ps",NULL);
        exit(0);
    }
}