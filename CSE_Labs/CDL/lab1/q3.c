#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 1000
char *strrev(char *str)
{
  char *p1, *p2;

  if (!str || !*str)
    return str;
  for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
  {
    *p1 ^= *p2;
    *p2 ^= *p1;
    *p1 ^= *p2;
  }
  return str;
}

int main(int argc, char *argv[])
{
  char *name1 = argv[1], *name2 = argv[2], *target = argv[3];
  char line2[MAX_LINE_LENGTH];
  char line1[MAX_LINE_LENGTH];
  FILE *textfile1, *textfile2, *targetfile;

  textfile1 = fopen(name1, "r");
  textfile2 = fopen(name2, "r");
  targetfile = fopen(target, "w");

  if (textfile1 == NULL || textfile2 == NULL)
    return 1;

  while (fgets(line1, MAX_LINE_LENGTH, textfile1) && fgets(line2, MAX_LINE_LENGTH, textfile2))
  {
    fputs(line1, targetfile);
    fputs(line2, targetfile);
  }
  while (fgets(line1, MAX_LINE_LENGTH, textfile1))
  {
    fputs(line1, targetfile);
  }
  while (fgets(line2, MAX_LINE_LENGTH, textfile2))
  {
    fputs(line2, targetfile);
  }

  fclose(textfile1);
  fclose(textfile2);
  fclose(targetfile);
  return 0;
}
