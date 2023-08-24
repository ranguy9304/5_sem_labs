#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>
//  CREATED BY RUDRA PATEL 210905324
//  ROLL 52
int main()
{
    int c[256];
int len,result,sockfd,n=1;
struct sockaddr_in address;
char ch[256],buf[256];
//Create a socket for the client
sockfd = socket(AF_INET, SOCK_STREAM, 0);
address.sin_family=AF_INET;
address.sin_addr.s_addr=inet_addr("127.0.0.1"); 
address.sin_port=htons(10200);
len = sizeof(address);
//Connect your socket to the server’s socket
result=connect(sockfd,(struct sockaddr *)&address,len);
if(result==-1)
{
perror("\nCLIENT ERROR");
exit(1);
}
//You can now read and write via sockfd (Logic for problem mentioned here)-------------------
printf("\nENTER SIZE\t");
scanf("%d",&c[0]);
printf("\nENTER ELEMENTS\t");
for(int k=1;k<=c[0];k++)
scanf("%d",&c[k]);

int temppid;
write(sockfd,&c,sizeof(c));
printf("STRING SENT BACK FROM SERVER IS ..... ");
n = read(sockfd,&c,sizeof(c));
if (n == -1)
    {
        perror("ERROR\n");
        exit(0);
    }
int temp[c[0]];
for(int k=1;k<=c[0];k++)
printf("%d ",c[k]);
printf("\n");

n = read(sockfd,&temppid,sizeof(temppid));
if (n == -1)
    {
        perror("ERROR\n");
        exit(0);
    }
printf("PID : %d",temppid);

// n=read(sockfd,buf,sizeof(buf));
// puts(buf);

}