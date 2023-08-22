#include<unistd.h>
#include<stdio.h>
#include<dirent.h>
#include<string.h>
#include<sys/stat.h>
#include<stdlib.h>
#include <errno.h>
void printdir(char *dir, int depth)
{
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;
    if((dp = opendir(dir)) == NULL) {
        fprintf(stderr,"cannot open directory: %s\n", dir);
        return;
    }
    chdir(dir);
    while((entry = readdir(dp)) != NULL) {
        lstat(entry->d_name,&statbuf);
        if(strcmp(".",entry->d_name) == 0 || strcmp("..",entry->d_name) == 0)
            continue;
        int returnval;
        printf("%*s%s------>\n",depth,"",entry->d_name);
        returnval = 0;
        char *filepath=entry->d_name;
        returnval = access (filepath, R_OK);
        if (returnval == 0)
        printf ("---%s has Read permissions.\n", filepath);
        else
        {
        if (errno == ENOENT)
        printf ("---%s No such file or directory.\n", filepath);
        else if (errno == EACCES)
        printf ("---%s Read Permission denied.\n", filepath);
        }// Check write access
        returnval = 0;
        returnval = access (filepath, W_OK);
        if (returnval == 0)
        printf ("---%s has Write permissions.!\n", filepath);
        else
        {
        if (errno == ENOENT)
        printf ("---%s No such file or directory.\n", filepath);
        else if (errno == EACCES)
        printf ("---%s Write Permission denied.\n", filepath);
        }// Check execute access
        returnval = 0;
        returnval = access (filepath, X_OK);
        if (returnval == 0)
        printf ("---%s has Execute permissions.!\n", filepath);
        else
        {
        if (errno == ENOENT)
        printf ("---%s No such file or directory.\n", filepath);
        else if (errno == EACCES)
        printf ("---%s Execute Permission denied.\n", filepath);
        
        }
        printf("\n\n");
    }
    chdir("..");
    closedir(dp);
}

int main(){
    printdir("/home/OS_Student/210905324_rudra",0);

    return 0;
}