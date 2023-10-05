#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "symbolTable.c"
#include "tokenizer.c"

#define max 20

// program - > main ( ) { declaration stat-list }
// id-list -> id idPrime
// idPrime -> epislon | , id-list | [number],id-list | [number]
// stat-list -> stat stat-list | epislon
// stat -> ass-stat ;
// ass-stat -> id = expn
// expn -> simp-exp eprime
// eprime -> relop simp_exp | epsilon
// simp-exp -> term seprime
// seprime -> addop term seprime | epsilon
// term -> factor tprime
// tprime -> mulop factor tprime | epsilon
// factor -> id | num
// relop -> == | != | <= | >= | > | <
// addop -> + | -
// mulop -> * | / | %

char c, buf[10];
int row = 0, column = 0;
FILE *fp, checkpoint;
Token retract;
// retract.row = 0;
int decl_flag = 1;
void id_list();
void listPrime()
{
    checkpoint = *fp;

    retract.row = 0;

    if (strcmp(getNextTokenTable().lexeme, ",") == 0)
        id_list();
    else
        *fp = checkpoint;
}
void id_list()
{

    retract.row = 0;

    if (getNextTokenTable().type == IDENTIFIER)
        listPrime();
}

void invalid()
{
    printf("Parse Unsuccessful\n");
    printf("Error at row %d and column %d\n", row, column);
}

void assignPrime()
{

    retract.row = 0;
    // retract = ;
    if (getNextTokenTable().type == IDENTIFIER)
    {
        // retract = getNextTokenTable();
        if (strcmp(getNextTokenTable().lexeme, ";") == 0)
            return;
    }
    else if (retract.type == NUMBER)
    {
        // retract = getNextTokenTable();
        if (strcmp(getNextTokenTable().lexeme, ";") == 0)
            return;
    }
    else
    {
        invalid();
        exit(0);
    }
}
void Assignment()
{

    retract.row = 0;

    if (getNextTokenTable().type == IDENTIFIER)
    {

        if (strcmp(getNextTokenTable().lexeme, "=") == 0)
            assignPrime();
        else
        {

            invalid();
            exit(0);
        }
    }
}

void data_type()
{

    retract = getNextTokenTable();

    if (strcmp(retract.lexeme, "int") == 0 || strcmp(retract.lexeme, "char") == 0)
        return;
    else
    {
        getPrevTokenTable();

        decl_flag = 0;
    }
}
void decleration()
{

    data_type();
    if (decl_flag)
        id_list();

    if (decl_flag && !strcmp(getNextTokenTable().lexeme, ";"))
        decleration();
    else
        getPrevTokenTable();
}
// factor -> id | num
bool factor()
{
    printToken(getCurTokenTable());
    printf("factor ->\n");
    if (getNextTokenTable().type == IDENTIFIER)
        return true;
    else
    {
        getPrevTokenTable();
        if (getNextTokenTable().type == NUMBER)
            return true;
        else
        {
            getPrevTokenTable();
            return false;
        }
    }
}
// tprime -> mulop factor tprime | epsilon
void tprime()
{
    if (getNextTokenTable().type == OPP)
    {

        factor();
        tprime();
    }
    else
        getPrevTokenTable();
}


// relop -> == | != | <= | >= | > | <
// addop -> + | -
// mulop -> * | / | %

// term -> factor tprime
void term()
{
    factor();
    tprime();
}
// seprime -> addop term seprime | epsilon
void seprime()
{
    if (getNextTokenTable().type == OPP)
    {

        term();
        seprime();
    }
    else
        getPrevTokenTable();
}
// simp-exp -> term seprime
void simp_exp()
{

    term();
    seprime();
}
// eprime -> relop simp_exp | epsilon
void eprime()
{
    if (getNextTokenTable().type == ROPP)
    {
        simp_exp();
    }
    else
        getPrevTokenTable();
}

// expn -> simp-expn eprime
void expn()
{
    simp_exp();
    eprime();
}
// ass-stat -> id = expn
void ass_stat()
{
    
    if (getNextTokenTable().type == IDENTIFIER)
    {
        printToken(getCurTokenTable());
        printf("ass-stat -> id\n");
        if (!strcmp(getNextTokenTable().lexeme, "=")){
            printf("ass-stat -> id =\n");
            }
        else
        {
            invalid();
            exit(0);
        }
        expn();
    }
    else
    {
        invalid(0);
        exit(0);
    }
}
// stat -> ass-stat ;
bool stat()
{
    ass_stat();
    if (!strcmp(getNextTokenTable().lexeme, ";"))
        return true;
    else
    {
        getPrevTokenTable();
        return false;
    }
}
// stat-list -> stat stat-list | epislon
bool stat_list()
{
    if (stat())
    {
        stat_list();
        printToken(getCurTokenTable());
        printf("stat stat-list\n");
        return true;
    }
    else{
        printToken(getCurTokenTable());
        printf("epsilon\n");
        return true;}
}
// program - > main ( ) { declaration statment-list }
void program()
{

    // retract.row = 0;
    int countt = 0;
    // retract = getNextTokenTable();

    if (!strcmp(getNextTokenTable().lexeme, "main"))
    {

        if (!strcmp(getNextTokenTable().lexeme, "("))
        {
            if (!strcmp(getNextTokenTable().lexeme, ")"))
            {
                if (!strcmp(getNextTokenTable().lexeme, "{"))
                {
                    decleration();
                    stat_list();
                    retract = getNextTokenTable();
                    printToken(retract);
                    if (strcmp(retract.lexeme, "}") == 0)
                    {
                        printf("Parse Successful");
                        exit(0);
                    }
                    else
                    {
                        invalid();
                        printf("Missing parentheses '\n");
                        exit(0);
                    }
                }
                else
                {
                    invalid();
                    exit(0);
                }
            }
            else
            {
                invalid();
                exit(0);
            }
        }
        else
        {
            invalid();
            exit(0);
        }
    }
    else
    {
        invalid();
        exit(0);
    }
}

int main()
{
    struct ListElement *TABLE[TableLength];
    Initialize(TABLE);

    fp = fopen("digit.c", "r");
    c = fgetc(fp);
    if (fp == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }
    storeTokens(c, fp, &row, &column);
    // printTokenIndexTable();
    program();
}