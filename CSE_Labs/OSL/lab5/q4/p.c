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
#define TEN_MEG (1024 * 1024 * 10)
int main()
{
    int pipe_fd;
    int res;
    int open_mode = O_WRONLY;
    int bytes_sent = 0;
    char buffer[BUFFER_SIZE + 1];
    if (access(FIFO_NAME, F_OK) == -1)
    {
        res = mkfifo(FIFO_NAME, 0777);
        if (res != 0)
        {
            fprintf(stderr, "Could not create fifo % s\n", FIFO_NAME);
            exit(EXIT_FAILURE);
        }
    }
    printf("Process % d opening FIFO O_WRONLY\n", getpid());
    pipe_fd = open(FIFO_NAME, open_mode);
    printf("Process % d result % d\n", getpid(), pipe_fd);
    char *data = "hello... this is sample data";
    int send[] = {1, 2, 3, 4};
    for (int i = 0; i < 4; i++)
    {
        write(pipe_fd, &send[i], sizeof(send[i]));
    }
    printf("Process % d finished\n", getpid());
    exit(EXIT_SUCCESS);
}