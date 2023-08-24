#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
int main()
{
    int sd;
    struct sockaddr_in address;
    sd = socket(AF_INET, SOCK_DGRAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1"); //**
    address.sin_port = htons(9704);

    int *rows=(int *)malloc(sizeof(int));
    int *columns=(int *)malloc(sizeof(int));
    
    printf("enter rows\n");
    // gets(buf);
    scanf("%d",rows);
    int len = sizeof(address);
    int m = sendto(sd, rows, sizeof(rows), 0, (struct sockaddr *)&address, len);
    printf("enter columns\n");
    // gets(buf);
    scanf("%d",columns);
    m = sendto(sd, columns, sizeof(columns), 0, (struct sockaddr *)&address, len);
    int *temp=(int *)malloc(sizeof(int)*(*columns));
    
    for(int i=0;i<*rows;i++){
        for(int j=0;j<*columns;j++){
            scanf("%d",&temp[j]);
        }
        
        m=sendto(sd,temp,sizeof(temp),0,(struct sockaddr *)&address,len);
        printf("---row sent---\n");

        
    }
    // int n=recvfrom(sd,&mat,sizeof(mat),0,(struct sockaddr *)&address,&len);
    // printf("matrix recieved");
    // printf("the server echo is\n");
    // puts(buf);
    return 0;
}