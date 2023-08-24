#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#define PORTNO 10200
int main()
{
int sockfd,newsockfd,portno,clilen,n=1;
struct sockaddr_in seraddr,cliaddr;
int i,value;
// create an unnamed socket for the server
sockfd = socket(AF_INET,SOCK_STREAM,0);
//Name the socket
seraddr.sin_family = AF_INET;
seraddr.sin_addr.s_addr = inet_addr("192.168.182.23");// **
seraddr.sin_port = htons(PORTNO);
bind(sockfd,(struct sockaddr *)&seraddr,sizeof(seraddr));
//Create a connection queue and wait for clients
listen(sockfd,5);
clilen = sizeof(clilen);
newsockfd=accept(sockfd,(struct sockaddr *)&cliaddr,&clilen);
while (n) {

char buf[256],buf1[256];
buf1[0]=" ";
strcpy(buf, "");
printf("server waiting");
//Accept a connection

//Read and write to client on client_sockfd (Logic for problem mentioned here)
n = read(newsockfd,buf,sizeof(buf));
printf(" \nMessage from Client %s \n",buf);
char word[100],twoD[10][30];
int i = 0, j = 0, k = 0, len1 = 0, len2 = 0, l = 0;
for (i = 0; buf[i] != '\0'; i++)

{

    if (buf[i] == ' ')

    {

        twoD[k][j] = '\0';

        k ++;

        j = 0;

    }

    else

    {

        twoD[k][j] = buf[i];

        j ++;

    }

}



twoD[k][j] = '\0';
    j = 0;

for (i = 0; i < k; i++)

{

    int present = 0;

    for (l = 1; l < k + 1; l++)

    {

        if (twoD[l][j] == '\0' || l == i)

        {

            continue;

        }



        if (strcmp (twoD[i], twoD[l]) == 0) {

            twoD[l][j] = '\0';

            present = present + 1;

        }

    }
        j = 0;
}

strcpy(buf1, "");
for (i = 0; i < k + 1; i++)

{
    printf("dfsd");

    if (twoD[i][j] == '\0')

        continue;

    else{
        strcat(buf1,twoD[i]);
        strcat(buf1," ");
        printf ("%s ", twoD[i]);
        }

}
        strcat(buf1,"\0");
        n = write(newsockfd,buf1,sizeof(buf1));
}
}
// RUDRA PATEL 210905324