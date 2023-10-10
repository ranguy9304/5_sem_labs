#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include<time.h>
int main(int argc, char *argv[])
{
    struct stat sb;
    int ret;
    if (argc < 2)
    {
        fprintf(stderr, "usage: %s <file>\n", argv[0]);
        return 1;
    }
    ret = stat(argv[1], &sb);
    if (ret)
    {
        perror("stat");
        return 1;
    }
    printf("---STATS---  %s \n", argv[1]);
    printf("device ID : %ld \n", sb.st_dev);
    printf("inode : %ld \n", sb.st_ino);
    printf("permissions : %d \n", sb.st_mode);
    printf("number of HARD LINKS : %ld \n", sb.st_nlink);
    printf("user ID : %d \n", sb.st_uid);
    printf("group ID : %d \n", sb.st_gid);
    printf("size  : %ld bytes \n", sb.st_size);
    printf("block size : %ld \n", sb.st_blksize);
    printf("number of blocks: %ld \n", sb.st_blocks);
    printf("last access time : %s \n", ctime(&sb.st_atime));
printf("last mod time : %s \n", ctime(&sb.st_mtime));
    printf("last stat change time : %s \n", ctime(&sb.st_ctime));









    return 0;
}