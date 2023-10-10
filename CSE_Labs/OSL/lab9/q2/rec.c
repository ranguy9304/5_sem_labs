// shm1.c – Consumer process
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "shm_com.h"
int main()
{
    char buffer[BUFSIZ];

    int running = 1;
    void *shared_memory = (void *)0;
    shared_use_st *shared_stuff;
    int shmid;
    srand((unsigned int)getpid());
    shmid = shmget((key_t)1234, sizeof(shared_use_st), 0666 | IPC_CREAT);
    if (shmid == -1)
    {
        fprintf(stderr, "shmget failed\n");
        exit(EXIT_FAILURE);
    }
    shared_memory = shmat(shmid, (void *)0, 0);
    if (shared_memory == (void *)-1)
    {
        fprintf(stderr, "shmat failed\n");
        exit(EXIT_FAILURE);
    }
    printf("Memory attached at %X\n", (int)shared_memory);
    shared_stuff = (shared_use_st *)shared_memory;
    shared_stuff->type = 0;
    pid_t id= fork();
    if(id){
        
        
        printf("Enter some text :");
        fgets(buffer, BUFSIZ, stdin);
        strncpy(shared_stuff->test, buffer, TEXT_SZ);
        shared_stuff->type = 1;
        while (shared_stuff->type == 1)
        {
            sleep(1);
            printf("waiting for client...\n");
        }
        if(shared_stuff->type == 2){
            printf("%s",shared_stuff->test);
            shared_stuff->type=3;
        }
        
        
    }
    else{
        while (shared_stuff->type == 0)
        {
            sleep(1);
            printf("waiting for parent...\n");
        }
        if(shared_stuff->type == 1){
            printf("RECIEVED REQUEST");
            shared_stuff->test[0] +=1;
            shared_stuff->type=2; 
        }
        while (shared_stuff->type != 3)
        {
            sleep(1);
            // printf("waiting for parent...\n");
        }


    }
    if (shmdt(shared_memory) == -1)
    {
        fprintf(stderr, "shmdt failed\n");
        exit(EXIT_FAILURE);
    }

    if (shmctl(shmid, IPC_RMID, 0) == -1)
    {
        fprintf(stderr, "shmctl(IPC_RMID) failed\n");
        exit(EXIT_FAILURE);
    }
    // shared_stuff->type = 0;
    exit(EXIT_SUCCESS);
}