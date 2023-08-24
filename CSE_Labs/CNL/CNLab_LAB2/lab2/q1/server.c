#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define PORTNO 10200

//  CREATED BY RUDRA PATEL 210905324
//  ROLL 52
int compare(const void *num1, const void *num2) // comparing function
{
    int a = *(int *)num1;
    int b = *(int *)num2;
    if (a > b)
    {
        return 1;
    }
    else if (a < b)
    {
        return -1;
    }
    return 0;
}
int main()
{
    int sockfd, newsockfd, portno, clilen, n = 1;
    int buf[256];
    struct sockaddr_in seraddr, cliaddr;
    int i, value;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        perror("ERROR\n");
        exit(0);
    }
    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr = inet_addr("127.0.0.1"); //**
    seraddr.sin_port = htons(PORTNO);
    bind(sockfd, (struct sockaddr *)&seraddr, sizeof(seraddr));
    // Create a connection queue, ignore child exit details, and wait for clients
    listen(sockfd, 5);
    while (1)
    {
        // Accept the connection
        clilen = sizeof(clilen);
        newsockfd = accept(sockfd, (struct sockaddr *)&cliaddr, &clilen);
        if (newsockfd == -1)
        {
            perror("ERROR\n");
            exit(0);
        }
        // Fork to create a process for this client and perform a test to see whether
        // you’re the parent or the child:
        if (fork() == 0)
        {
            // If you’re the child, you can now read/write to the client on newsockfd.
            n = read(newsockfd, &buf, sizeof(buf));
            if (n == -1)
            {
                perror("ERROR\n");
                exit(0);
            }
            int temp[buf[0]];
            for (int k = 1; k <= buf[0]; k++)
                temp[k - 1] = buf[k];
            qsort(&temp, buf[0], sizeof(int), compare);
            int temp1[buf[0] + 1];
            temp1[0] = buf[0];
            for (int k = 1; k <= buf[0]; k++)
                temp1[k] = temp[k - 1];
            printf("MESSAGE SENDING TO CLIENT --> ");
            for (int k = 1; k <= buf[0]; k++)
                printf("%d ", temp1[k]);
            printf("\n");

            n = write(newsockfd, temp1, sizeof(temp1));
            if (n == -1)
            {
                perror("ERROR\n");
                exit(0);
            }
            int sendpid = getpid();
            n = write(newsockfd, sendpid, sizeof(sendpid));
            if (n == -1)
            {
                perror("ERROR\n");
                exit(0);
            }
            close(newsockfd);
            exit(0);
        }
        // Otherwise, you must be the parent and your work for this client is finished
        else
            close(newsockfd);
    }
}