#include<unistd.h>
#include<stdio.h>
#include<dirent.h>
#include<string.h>
#include<sys/stat.h>
#include<stdlib.h>
#include <errno.h>
 


void printdir( char *dir, int depth)
{
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;
    char* arr[100];
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
            

        }

        else {printf("%*s%s\n",depth,"",entry->d_name);
        arr[count]=entry->d_name;
            // printf("%*s%s/\n",depth,"",entry->d_name);
            // /* Recurse at a new indent level */
            // printdir(entry->d_name,depth+4);
            count++;
        }
    }
 
    for (int i = 0; i < count; i++){
        printf("%d: %s \n", i, arr[i]);
       }
    printf("ENTER -1 TO DELETE ALL\n\tOR\nENTER THE INDEX OF FILE YOU WANT TO DELETE");
    int input,ret;
    scanf("%d",&input);
    FILE *fp;
    if(input>=0){
        // fp = fopen(arr[input], "w");
        // fclose(fp);
        ret = remove(arr[input]);

        if(ret == 0) {
            printf("File deleted successfully");
        } else {
            printf("Error: unable to delete the file");
        }
        
    }
    else{
        for (int i = 0; i < count; i++){
        // fp = fopen(arr[i], "w");
        ret = remove(arr[i]);

        if(ret == 0) {
            printf("File deleted successfully");
        } else {
            printf("Error: unable to delete the file");
        }
        // fclose(fp);
       }
        
    }
    chdir("..");
    closedir(dp);
}
int main(){
    printdir("/home/OS_Student/210905324_rudra/lab2/",0);

    return 0;
}