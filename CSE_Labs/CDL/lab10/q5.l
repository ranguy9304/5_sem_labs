%{
    #include<stdio.h>
    #include<string.h>
int pos_int = 0;
int neg_int = 0;
int pos_flt = 0;
int neg_flt =0 ;
%}
%%
[1-9][0-9]* {fprintf(yyout, "%X",atoi(yytext));}
"printf" {fprintf(yyout, "%s","write");}
.       { fprintf(yyout, "%s", yytext); }
%%
 
 
 
// driver code 
int main()
{
 
    /* yyin and yyout as pointer
    of File type */
    extern FILE *yyin, *yyout;
 
    /* yyin points to the file input.txt
    and opens it in read mode*/
    yyin = fopen("Input.txt", "r");
 
    /* yyout points to the file output.txt
    and opens it in write mode*/
    yyout = fopen("Output.txt", "w");
 
    yylex();
    return 0;
}
int yywrap()
{
return 1;
}