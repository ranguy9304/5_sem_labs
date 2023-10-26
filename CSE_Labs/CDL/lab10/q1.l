%{
int chars = 0;
int words = 0;
int lines = 0;
int vowels = 0;
%}
%%

[a,e,i,o,u,A,E,I,O,U] {vowels++;}
%%
int main(int argc, char **argv)
{
yylex();
printf("%d %d %d %d\n", lines, words, chars,vowels); }
int yywrap()
{
return 1;
}