#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define PORTNO 10200
//  CREATED BY RUDRA PATEL 210905324
//  ROLL 52

int main()
{
    int sockfd, newsockfd, portno, clilen, n = 1;

    struct sockaddr_in seraddr, cliaddr;
    int i, value;
    int v1, v2, res = 0;
    char ops;
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
            n = read(newsockfd, &v1, sizeof(v1));
            if (n == -1)
            {
                perror("ERROR\n");
                exit(0);
            }

            n = read(newsockfd, &v2, sizeof(v2));
            if (n == -1)
            {
                perror("ERROR\n");
                exit(0);
            }

            n = read(newsockfd, &ops, sizeof(ops));
            if (n == -1)
            {
                perror("ERROR\n");
                exit(0);
            }
            printf("%d", v1);
            printf("%c", ops);
            printf("%d", v2);
            if (ops == '+')
            {
                res = v1 + v2;
            }
            if (ops == '-')
            {
                res = v1 - v2;
            }
            if (ops == '/')
            {
                res = v1 / v2;
            }
            if (ops == '*')
            {
                res = v1 * v2;
            }
            printf("MESSAGE SENDING TO CLIENT --> ");
            printf("%d", res);

            n = write(newsockfd, res, sizeof(res));
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