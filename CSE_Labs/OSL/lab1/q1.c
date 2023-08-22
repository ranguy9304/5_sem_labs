#include<stdio.h> 
#include<stdlib.h>
#include<string.h> 
#define MAX_LINE_LENGTH 1024
int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s  \n", argv[0]);
        exit(1);
    }
    
    char *pattern = argv[1];
    char *filename = argv[2];
    FILE *fp;
    char line[MAX_LINE_LENGTH];
    int line_number = 1;
    int match_found = 0;
    
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error: could not open file %s\n", filename);
        exit(1);
    }
    
    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
        if (strstr(line, pattern) != NULL) {
            printf("%s:%d:%s", filename, line_number, line);
            match_found = 1;
        }
        line_number++;
    }
    
    if (!match_found) {
        printf("No matches found for %s in %s\n", pattern, filename);
    }
    
    fclose(fp);
    return 0;
}