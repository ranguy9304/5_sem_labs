#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main(int argc, char *argv[])
{
	char *name= argv[1];
	FILE *fptr;
	fptr=fopen(name,"r");
	if (fptr == NULL)
	{
		printf("Cannot open file %s \n", name);
		exit(0);
	}
	int countc=0,countl=0;
	char c;
	c = fgetc(fptr);
	// Read contents from file
	while (c != EOF)
	{
		if (c=='\n'){
			countl++;
		}
		else if (c!=' '){
			countc++;


		}
		c = fgetc(fptr);
	}
	if (countc>0){
		countl++;
	}
	printf("lines : %d \nchars : %d",countl,countc);

	return 0;
}