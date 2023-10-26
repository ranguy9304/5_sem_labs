%{
    #include<stdio.h>
    #include<string.h>
int pos_int = 0;
int neg_int = 0;
int pos_flt = 0;
int neg_flt =0 ;
%}
%%
[+-]?[0-9]*\.[0-9]* {printf("float");if(yytext[0] == '-'){neg_flt++;}else{pos_flt++;} }
[+-]?[0-9]* {printf("int");if(yytext[0] == '-'){neg_int++;}else{pos_int++;}}
%%
int main(int argc, char **argv)
{
yylex();
printf("pint %d \nnint %d \npflt %d \nnflt %d\n", pos_int, neg_int,pos_flt,neg_flt); }
int yywrap()
{
return 1;
}