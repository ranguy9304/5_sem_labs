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
sockfd = socket(AF_INET,SOCK_STREAM,0);
seraddr.sin_family = AF_INET;
seraddr.sin_addr.s_addr = inet_addr("192.168.182.23");// **
seraddr.sin_port = htons(PORTNO);
bind(sockfd,(struct sockaddr *)&seraddr,sizeof(seraddr));
listen(sockfd,5);
while (1) {
char buf[256];
printf("server waiting");
clilen = sizeof(clilen);
newsockfd=accept(sockfd,(struct sockaddr *)&cliaddr,&clilen);
n = read(newsockfd,buf,sizeof(buf));
printf(" \nENCRYPTED Message from Client %s \n",buf);
for(int i =0;i<strlen(buf);i++){
    buf[i]-=4;
}
printf(" \nDECRYPTED  Message from Client %s \n",buf);
n = write(newsockfd,buf,sizeof(buf));
}
}
// RUDRA PATEL 210905324