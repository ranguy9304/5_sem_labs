#include<unistd.h>
#include<stdio.h>
#include<dirent.h>
#include<string.h>
#include<sys/stat.h>
#include<stdlib.h>
#include <errno.h>
 
// Defining comparator function as per the requirement
static int myCompare(const void* a, const void* b)
{
    return strcmp(*(const char**)a, *(const char**)b);
}
 
// Function to sort the array
void sort(const char* arr[], int n)
{
    qsort(arr, n, sizeof(const char*), myCompare);
}
void printdir(const char *dir, int depth)
{
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;
    const char* arr[100];
    if((dp = opendir(dir)) == NULL) {
        fprintf(stderr,"cannot open directory: %s\n", dir);
        return;
    }
    chdir(dir);
    int count=0;
    while((entry = readdir(dp)) != NULL) {
        lstat(entry->d_name,&statbuf);
        if(S_ISDIR(statbuf.st_mode)) {
            /* Found a directory, but ignore . and .. */
            if(strcmp(".",entry->d_name) == 0 || strcmp("..",entry->d_name) == 0)
            continue;
            arr[count]=entry->d_name;
            count++;
        }
        else printf("%*s%s\n",depth,"",entry->d_name);
    }
    sort(arr, count);
    for (int i = 0; i < count; i++){
        printf("%d: %s \n", i, arr[i]);
        printdir(arr[i],depth+4);}

    chdir("..");
    closedir(dp);
}
int main(){
    printdir("/home/OS_Student/210905324_rudra",0);
    return 0;
}