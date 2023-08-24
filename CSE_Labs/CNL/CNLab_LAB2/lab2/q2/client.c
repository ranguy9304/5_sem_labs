#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
//  CREATED BY RUDRA PATEL 210905324
//  ROLL 52
int main()
{
    int v1, v2, res;
    char ops;
    int len, result, sockfd, n = 1;
    struct sockaddr_in address;
    char ch[256], buf[256];
    // Create a socket for the client
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        perror("ERROR\n");
        exit(0);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(10200);
    len = sizeof(address);
    // Connect your socket to the server’s socket
    result = connect(sockfd, (struct sockaddr *)&address, len);
    if (result == -1)
    {
        perror("ERROR\n");
        exit(0);
    }
    if (result == -1)
    {
        perror("\nCLIENT ERROR");
        exit(1);
    }
    // You can now read and write via sockfd (Logic for problem mentioned here)
    printf("\nENTER V1\t");
    scanf("%d", &v1);
    printf("\nENTER V2\t");
    scanf("%d", &v2);
    printf("\nENTER OP\t");
    scanf("%c", &ops);
    scanf("%c", &ops);
    write(sockfd, &v1, sizeof(v1));
    write(sockfd, &v2, sizeof(v2));
    write(sockfd, &ops, sizeof(ops));
    printf("STRING SENT BACK FROM SERVER IS ..... ");
    n = read(sockfd, &res, sizeof(res));
    if (n == -1)
    {
        perror("ERROR\n");
        exit(0);
    }

    printf("RESULT : %d", res);

    // n=read(sockfd,buf,sizeof(buf));
    // puts(buf);
}