#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "symbolTable.c"
#include "tokenizer.c"
#define max 20
int push(char stack[max][80], int *top, char data[80])
{
    if (*top == max - 1)
        return (-1);
    else
    {
        *top = *top + 1;
        strcpy(stack[*top], data);
        return (1);
    }
}
int pop(char stack[max][80], int *top, char data[80])
{
    if (*top == -1)
        return (-1);
    else
    {
        strcpy(data, stack[*top]);
        *top = *top - 1;
        return (1);
    }
}
bool isEmpty(char stack[max][80], int *top)
{
    if (*top == -1)
        return true;
    else
        return false;
}
// int main()
// {
char stack[max][80], nm[80];
int top=-1, ch, reply;
// top = -1; // Initialize Stack

char *capitalizeString(char *str)
{
    // Check if the input string is not empty
    if (str == NULL || *str == '\0')
    {
        return str;
    }

    // Capitalize the first character
    *str = toupper(*str);

    // Iterate through the rest of the string and capitalize subsequent letters
    int count = sizeof(str) / sizeof(str[0]);
    // printf("%d",count);
    for (int i = 1; str[i] != '\0'; i++)
    {
        // printf("%c",str[i]);

        str[i] = toupper(str[i]);
        // printf("%c",str[i]);
    }

    return str;
}

int checkST(Token tk, char c, FILE *fp, int *row, int *column, struct ListElement *TABLE[TableLength], int type)
{
    Token temp;
    // char temp11=[0];
    enum dataType contextType = enumString(capitalizeString(tk.lexeme));
    temp = getNextToken(c, fp, row, column);
    printToken(temp);
    char tempIdentifierHolder[40];
    if (temp.type == IDENTIFIER)
    {
        strcpy(tempIdentifierHolder, temp.lexeme);
        temp = getNextToken(c, fp, row, column);
        printToken(temp);
        if (!strcmp(temp.lexeme, "(") && type == 0)
        {
            if (!SEARCH(tempIdentifierHolder, TABLE))
            {
                struct TableToken tk;
                tk.lexeme = (char *)malloc(sizeof(char) * 40);
                strcpy(tk.lexeme, tempIdentifierHolder);
                int tempargscount = 0;

                while (strcmp(temp.lexeme, ")"))
                {
                    printf("in");
                    temp = getNextToken(c, fp, row, column);
                    if (temp.type == IDENTIFIER)
                    {
                        strcpy(tempIdentifierHolder, temp.lexeme);
                        // temp=getNextToken(c,fp,row,column);

                        if (!SEARCH(tempIdentifierHolder, TABLE))
                        {
                            struct TableToken tk;
                            tk.lexeme = (char *)malloc(sizeof(char) * 40);
                            strcpy(tk.lexeme, tempIdentifierHolder);

                            tempargscount += 1;
                        }
                    }
                }
                tk.argsCount = tempargscount;
                tk.dataType = NONEDT;
                tk.index = -1;
                tk.returnType = contextType;
                printf("tst \n %s",tk.lexeme);
                Initialize(tk.LOCALTABLE);
                // printToken(tk);
                //-----------------------------------
                Token retract;
                retract.row = 0;
                int countt = 0;
                push(stack, &top, "{");
                retract = getNextToken(c, fp, row, column);
                int countbrack=1;
                while (!isEmpty(stack, &top) )
                // while(countt<6)
                {
                    retract = getNextToken(c, fp, row, column);
                    printf("retract\n");
                    printToken(retract);
                    if(!strcmp(retract.lexeme,"{"))
                    {
                        push(stack, &top, "{");
                        countbrack+=1;
                        printf("pushed %d\n",countbrack);
                    }
                    else if(!strcmp(retract.lexeme,"}"))
                    {
                        pop(stack, &top, nm);
                        printf("pushed %d\n",countbrack);
                    }
                    if (retract.type == DATATYPE)
                    {
                        checkST(retract, c, fp, row, column, tk.LOCALTABLE, 1);
                    }
                    countt += 1;
                    // Display();
                }
                INSERT(tk, TABLE);
            }
        }
        else if ((!strcmp(temp.lexeme, "=") || !strcmp(temp.lexeme, ",") || !strcmp(temp.lexeme, "[")) && (type == 0 || type == 1))
        {
            // temp=getNextToken(c,fp,row,column);
            // printToken(temp);
            // temp=getNextToken(c,fp,row,column);
            // printToken(temp);
            // printf("charr");
            while (strcmp(temp.lexeme, ";"))
            {
                if (temp.type == IDENTIFIER)
                {
                    strcpy(tempIdentifierHolder, temp.lexeme);
                    // temp=getNextToken(c,fp,row,column);

                    if (!SEARCH(tempIdentifierHolder, TABLE))
                    {
                        struct TableToken tk;
                        tk.lexeme = (char *)malloc(sizeof(char) * 40);
                        strcpy(tk.lexeme, tempIdentifierHolder);

                        tk.argsCount = 0;
                        tk.dataType = contextType;
                        tk.index = -1;
                        tk.returnType = NONEDT;

                        INSERT(tk, TABLE);
                    }
                }
                else if (!strcmp(temp.lexeme, "="))
                {
                    if (!SEARCH(tempIdentifierHolder, TABLE))
                    {
                        struct TableToken tk;
                        tk.lexeme = (char *)malloc(sizeof(char) * 40);
                        strcpy(tk.lexeme, tempIdentifierHolder);

                        tk.argsCount = 0;
                        tk.dataType = contextType;
                        tk.index = -1;
                        tk.returnType = NONEDT;

                        INSERT(tk, TABLE);
                    }
                }
                else if (!strcmp(temp.lexeme, ","))
                {

                    if (!SEARCH(tempIdentifierHolder, TABLE))
                    {
                        struct TableToken tk;
                        tk.lexeme = (char *)malloc(sizeof(char) * 40);
                        strcpy(tk.lexeme, tempIdentifierHolder);

                        tk.argsCount = 0;
                        tk.dataType = contextType;
                        tk.index = -1;
                        tk.returnType = NONEDT;

                        INSERT(tk, TABLE);
                    }
                }
                // else if (!strcmp(temp.lexeme, "["))
                // {

                //     if (!SEARCH(tempIdentifierHolder, TABLE))
                //     {
                //         struct TableToken tk;
                //         tk.lexeme = (char *)malloc(sizeof(char) * 40);
                //         strcpy(tk.lexeme, tempIdentifierHolder);

                //         tk.argsCount = 0;
                //         tk.dataType = contextType;
                //         tk.index = -1;
                //         tk.returnType = NONEDT;

                //         INSERT(tk, TABLE);
                //     }
                // }

                temp = getNextToken(c, fp, row, column);
                // printToken(temp);
            }
        }

        else if (!strcmp(temp.lexeme, ")"))
        {
            printf("conversion");
            return 0;
        }
        else
        {
            printf("NOT VALID");
            return 0;
        }
    }
}

int main()
{
    struct ListElement *TABLE[TableLength];
    Initialize(TABLE);
    char c, buf[10];
    FILE *fp = fopen("digit.c", "r");
    c = fgetc(fp);
    if (fp == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }
    int row = 0, column = 0;
    // printf("sdf");
    Token retract;
    retract.row = 0;
    int countt = 0;
    // while (retract.row != -1)
    while(countt<6)
    {
        retract = getNextToken(c, fp, &row, &column);
        // printToken(retract);
        if (retract.type == DATATYPE)
        {
            checkST(retract, c, fp, &row, &column, TABLE, 0);
        }
        countt += 1;
        // Display();
    }
    Display(TABLE);
}