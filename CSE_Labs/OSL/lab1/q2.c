#include<stdio.h> 
#include<stdlib.h>
#include<string.h> 
#define MAX_LINE_LENGTH 1024
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s  \n", argv[0]);
        exit(1);
    }
    
    char *filename = argv[1];
    FILE *fp;
    char line[MAX_LINE_LENGTH];
    int line_number = 1;
    int delay=0;
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error: could not open file %s\n", filename);
        exit(1);
    }
    
    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
        
        line_number++;
        printf("%s:%d:%s", filename, line_number, line);
        if (line_number%20==0){
            fgetc(stdin);
        }
    }

    fclose(fp);
    return 0;
}