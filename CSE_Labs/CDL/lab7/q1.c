#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "symbolTable.c"
#include "tokenizer.c"
#define max 20

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
void Decleration()
{

    data_type();
    if (decl_flag)
        id_list();

    if (decl_flag && !strcmp(getNextTokenTable().lexeme, ";"))
        Decleration();
    else
        getPrevTokenTable();
}

void ProgramStart()
{

    retract.row = 0;
    int countt = 0;
    retract = getNextTokenTable();

    if (retract.row != -1 && !strcmp(retract.lexeme, "main"))
    {
        retract = getNextTokenTable();
        if (retract.row != -1 && !strcmp(retract.lexeme, "("))
        {
            retract = getNextTokenTable();
            if (retract.row != -1 && !strcmp(retract.lexeme, ")"))
            {
                retract = getNextTokenTable();
                if (retract.row != -1 && !strcmp(retract.lexeme, "{"))
                {
                    Decleration();
                    Assignment();
                    retract = getNextTokenTable();
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
    printTokenIndexTable();
    ProgramStart();
}