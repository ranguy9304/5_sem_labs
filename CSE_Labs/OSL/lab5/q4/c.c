#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#define FIFO_NAME "my_fifo"
#define BUFFER_SIZE 1000
int main()
{
    int pipe_fd;
    int res[4];
    int open_mode = O_RDONLY;
    char buffer[BUFFER_SIZE + 1];
    int bytes_read = 0;
    memset(buffer, '\0', sizeof(buffer));
    printf("Process % d opening FIFO O_RDONLY\n", getpid());
    pipe_fd = open(FIFO_NAME, open_mode);

    if (pipe_fd != -1)
    {
      
            
        read(pipe_fd, res, sizeof(res));
  

        (void)close(pipe_fd);
    }
    else
    {
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < 4; i++)
    {
        printf("%d ",res[i]);
    }
    printf("\n");
    printf("Process % d finished, % d bytes read\n", getpid(), bytes_read);
    exit(EXIT_SUCCESS);
}