
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
  

int main(int argc, char *argv[])
{
    FILE* ptr;
    FILE* targetfile;
    char ch;
    char* filename=argv[1];
    char* target=argv[2];
    targetfile=fopen(target,"w");
    ptr = fopen(filename, "r");
    if (NULL == ptr) {
        printf("file can't be opened \n");
    }
    do {
        ch = fgetc(ptr);
        fputc(ch,targetfile);
        // printf("%c", ch);

    } while (ch != EOF);
    printf("content copied successfully to file %s ",target);
    fclose(ptr);
    return 0;
}