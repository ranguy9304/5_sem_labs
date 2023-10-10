#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int n;       // size of fibonacci sequence.
int *arry; // arry holds the value of each fibonacci term.
int i;       // counter for the threads.

void *runn(void *arg);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("format is:./a.out <intgervalue>\n");
        return -1;
    } // valdiate num of args.

    if (atoi(argv[1]) < 0)
    {
        printf("%d must be>=0\n", atoi(argv[1]));
        return -1;
    } // valdiate value of arg1.

    n = atoi(argv[1]);
    arry = (int *)malloc(n * sizeof(int));
    for(int k=0;k<n;k++){
        scanf("%d",&arry[k]);
    }
    pthread_t thread ;
    pthread_attr_t attr; // set of thread attribute

    pthread_attr_init(&attr);

 
    pthread_create(&thread, &attr, runn, NULL);
    pthread_join(thread, NULL);


    // End of wating the threads to exit.

    // printing arry.
    printf("The SUM :");
    int k;

 
    printf("%d,", i);

    return 0;
} // End of main.

void *runn(void *arg)
{
    i=0;
    for(int k=0;k<n;k++){
        if(arry[k]>=0)
        i+=arry[k];
    }

} // End of run.
