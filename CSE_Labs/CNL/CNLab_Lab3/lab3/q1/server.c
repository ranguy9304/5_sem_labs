#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
int main()
{
    int sd;
    char buf[25];
    int *rows=(int *)malloc(sizeof(int));
    int *columns=(int *)malloc(sizeof(int));
    
    struct sockaddr_in sadd, cadd;
    // Create a UDP socket
    sd = socket(AF_INET, SOCK_DGRAM, 0);
    // Construct the address for use with sendto/recvfrom... */
    sadd.sin_family = AF_INET;
    sadd.sin_addr.s_addr = inet_addr("127.0.0.1"); //**
    sadd.sin_port = htons(9704);
    int result = bind(sd, (struct sockaddr *)&sadd, sizeof(sadd));
    int len = sizeof(cadd);
    int m = recvfrom(sd, rows, sizeof(rows), 0, (struct sockaddr *)&cadd, &len);
    printf("ROWS : %d \n",*rows);
    int **mat=(int **)malloc(sizeof(int *)*(*rows));


    m = recvfrom(sd, columns, sizeof(columns), 0, (struct sockaddr *)&cadd, &len);
    
    printf("COLUMNS : %d \n",*columns);
    // int mat[*rows][*columns];
    for(int i=0;i <*rows;i++){
        mat[i]=(int *)malloc(sizeof(int)*(*columns));
        m=recvfrom(sd,mat[i],sizeof(mat[i]),0,(struct sockaddr *)&cadd,&len);
    // printf("number of columns : %d",columns);

    }
    printf("recieved\n");
    for(int i=0;i <*rows;i++){
        // int m=recvfrom(sd,mat[i],sizeof(mat[i]),0,(struct sockaddr *)&cadd,&len);
    // printf("number of columns : %d",columns);
        for(int j=0;j<*columns;j++){
            printf("%d ",mat[i][j]);
        }
        printf("\n");
    }
    int n=sendto(sd,&mat,sizeof(mat),0,(struct sockaddr *)&cadd,len);
    if(n==-1)
    {
        perror("\nConnection Error\n");
        exit(1);
    }
    n = sendto(sd, buf, sizeof(buf), 0, (struct sockaddr *)&cadd, len);
    return 0;
}