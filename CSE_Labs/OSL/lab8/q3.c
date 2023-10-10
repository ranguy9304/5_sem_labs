
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
int n1;
int n2;      // size of fibonacci sequence.
bool *prime; // arry holds the value of each fibonacci term.
int i;       // counter for the threads.
int size;
void *runn(void *arg);
int nothreads ;
int chunks;
typedef struct thread_data
{
    int start;
    int end;

} thread_data;

// int main(int argc, char *argv[])
int main()
{
    // if (argc != 3)
    // {
    //     printf("format is:./a.out <intgervalue>\n");
    //     return -1;
    // } // valdiate num of args.

    // if (atoi(argv[1]) < 0)
    // {
    //     printf("%d must be>=0\n", atoi(argv[1]));
    //     return -1;
    // } // valdiate value of arg1.

    // n1 = atoi(argv[1]);

    // n2 = atoi(argv[2]);
    n1 = 1;
    n2 = 10;
    size = n2 - n1 + 1;
    prime = (bool *)malloc(size * sizeof(bool));
    // bool prime[n + 1];
    memset(prime, false, sizeof(prime));
    nothreads=size/2;

    pthread_t *threads = (pthread_t *)malloc(nothreads * sizeof(pthread_t));
    pthread_attr_t attr; // set of thread attribute

    pthread_attr_init(&attr);
    
    chunks = 2;
    int rem = size % chunks;
    printf("%d %d->\n",chunks,rem);
    thread_data *t = (thread_data *)malloc(sizeof(thread_data));
    // t[0].start = 7;
    // t[0].end = n1 + chunks-1;
    if (rem == 0)
    {
        for (i = 0; i < nothreads; i++)
        {
            t = (thread_data *)malloc(sizeof(thread_data));
            t[0].start = n1;
            t[0].end = n1 + chunks-1;
            // printf("sewwg %d ,%d\n",t[0].start,t[0].end);
            pthread_create(&threads[i], &attr, runn, (void *)t);
            pthread_join(threads[i], NULL);
            n1 += chunks;
            // thread_data *t = (thread_data *)malloc(sizeof(thread_data));
            // t[0].start = n1;
            // t[0].end = n1 + chunks-1;
            // printf("sewwg %d ,%d\n",t[0].start,t[0].end);
            // if(n1>10)
            // break;
        } // End of creating threads.
    }
    else
    {
        if (size < nothreads)
        {
            thread_data *t = (thread_data *)malloc(sizeof(thread_data));
            t[0].start = n1;
            t[0].end = n2;
            pthread_create(&threads[nothreads - 1], &attr, runn, (void *)t);
            pthread_join(threads[nothreads - 1], NULL);
        }
        else
        {
            for (i = 0; i < nothreads - 1; i++)
            {
                pthread_create(&threads[i], &attr, runn, (void *)t);
                pthread_join(threads[i], NULL);
                n1 += chunks;
                thread_data *t = (thread_data *)malloc(sizeof(thread_data));
                t[0].start = n1;
                t[0].end = n1 + chunks;
            }
        }

        t[0].end = t[0].end - (chunks - rem);
        pthread_create(&threads[nothreads - 1], &attr, runn, (void *)t);
        pthread_join(threads[nothreads - 1], NULL);
    }

    // End of wating the threads to exit.

    // printing arry.
    for (int p = 0; p < size; p++)
        if (prime[p])
            printf("%d ", p );

    return 0;
} // End of main.

void *runn(void *arg)
{
    thread_data *tdata = (thread_data *)arg;


    int start = tdata[0].start;
    int end = tdata[0].end;
    // printf("START %d END %d\n",start,end);
    for (int p = start; p <= end; p++)
    {
        int c = 0;
        for (int j = 1; j <= p; j++)
        {
            if (p % j == 0)
            {
                c++;
            }
        }

        if (c == 2)
        {
            prime[p-n1] = true;
            printf("prime %d\n",p);
        }
    }

} // End of run.

// void SieveOfEratosthenes(int n)
// {

//     // Create a boolean array "prime[0..n]" and initialize
//     // all entries it as true. A value in prime[i] will
//     // finally be false if i is Not a prime, else true.
//     // bool prime[n + 1];
//     // memset(prime, true, sizeof(prime));

//     for (int p = 2; p * p <= n; p++)
//     {
//         // If prime[p] is not changed, then it is a prime
//         if (prime[p] == true)
//         {
//             // Update all multiples of p greater than or
//             // equal to the square of it numbers which are
//             // multiple of p and are less than p^2 are
//             // already been marked.
//             for (int i = p * p; i <= n; i += p)
//                 prime[i] = false;
//         }
//     }

//     // Print all prime numbers
//     // for (int p = 2; p <= n; p++)
//     // 	if (prime[p])
//     // 		printf("%d ",p);
// }
