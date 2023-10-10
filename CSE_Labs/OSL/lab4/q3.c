#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

void main() {

    /*
        How to execute

        Create 2 folders Temp1 and Temp2 in Documents, and create a Text.txt inside Temp1 folder
        Execute this file and put the pathnames as shown
        After execution, you will see in the File Explorer that Text.txt is shifted from Temp1 to Temp2

        *Note*
        If you comment out the unlink part, then you will be able to see the Text.txt from both Temp1 and Temp2 folders
    */

    char PathOld[100], PathNew[100];
    printf("old path ");
    scanf("%s", PathOld); //    /home/student/Documents/Temp1/Text.txt
    printf("new path "); //    /home/student/Documents/Temp2/Text.txt
    scanf("%s", PathNew);
    int res = link(PathOld, PathNew);
    if (res == 0) {
        res = unlink(PathOld);
        if (res == 0)
            printf("path to the file: %s\n", PathNew);
        else
            printf("Error unlinking\n");
    }
    else
        printf("Error linking\n");
}

