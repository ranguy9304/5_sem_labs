#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 #include <sys/stat.h>
#define MAX_LINE_LENGTH 1000
char *strrev(char *str)
{
      char *p1, *p2;

      if (! str || ! *str)
            return str;
      for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
      {
            *p1 ^= *p2;
            *p2 ^= *p1;
            *p1 ^= *p2;
      }
      return str;
}
 
int main(int argc, char *argv[]) {
    char    *name=argv[1],*target=argv[2];
    char    line[MAX_LINE_LENGTH];
    char *text;
    FILE *textfile,*targetfile;
     
    textfile = fopen(name, "r");
	targetfile = fopen(target, "w");
	fseek(textfile, 0L, SEEK_END);
    long numbytes = ftell(textfile);
    fseek(textfile, 0L, SEEK_SET);  
    text = (char*)calloc(numbytes, sizeof(char));   
    if(textfile == NULL)
        return 1;
    fread(text, sizeof(char), numbytes, textfile);
    fputs(strrev(text),targetfile);
    struct stat st;
    long size;
    if (stat(name, &st) == 0)
    {
        size = st.st_size;
        printf("The size of the file is %ld bytes.\n", size);
    }
    fclose(textfile);
    fclose(targetfile);
    return 0;
}
