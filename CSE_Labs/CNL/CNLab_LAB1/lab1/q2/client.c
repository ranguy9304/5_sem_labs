#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>

int main()
{
int len,result,sockfd,n=1;
struct sockaddr_in address;
char ch[256],buf[256];
//Create a socket for the client
sockfd = socket(AF_INET, SOCK_STREAM, 0);
//Name the socket as agreed with the server
address.sin_family=AF_INET;
address.sin_addr.s_addr=inet_addr("192.168.182.23"); 
address.sin_port=htons(10200);
len = sizeof(address);
//Connect your socket to the server’s socket
result=connect(sockfd,(struct sockaddr *)&address,len);
if(result==-1)
{
perror("\nCLIENT ERROR");
exit(1);
}
//You can now read and write via sockfd (Logic for problem mentioned here)
while(1){
    printf("\nENTER STRING\t");
    char ch[256],buf[256];
    strcpy(ch," ");
    strcpy(buf," ");
    gets(ch);
    if (strcmp(ch,"exit")==0){
        break;
    }
    ch[strlen(ch)]='\0';
    write(sockfd,ch,strlen(ch));
    printf("STRING SENT BACK FROM SERVER IS ..... ");

    // for(int i=strlen(ch);i>0;i--){
    //     n=read(sockfd,buf,sizeof(buf));
    //     puts(buf);

    // }
    
    n=read(sockfd,buf,sizeof(buf));
    puts(buf);

    
    
  
}
}
// RUDRA PATEL 210905324