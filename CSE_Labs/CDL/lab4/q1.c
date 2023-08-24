#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "symbolTable.c"
#include "tokenizer.c"
int checkST(Token tk,char c, FILE *fp, int *row, int *column){
    Token temp;
    enum dataType contextType=tk.type;
    temp=getNextToken(c,fp,row,column);
    char tempIdentifierHolder[40];
    if(temp.type==IDENTIFIER){
        strcpy(tempIdentifierHolder,temp.lexeme);
        temp=getNextToken(c,fp,row,column);
        if(!strcmp(temp.lexeme,"(")){
            if(!SEARCH(tempIdentifierHolder)){
                struct TableToken tk;
                tk.lexeme=(char *)malloc(sizeof(char)*40);
                strcpy(tk.lexeme,tempIdentifierHolder);
            
                tk.argsCount=0;
                tk.dataType=NONE;
                tk.index=-1;
                tk.returnType=contextType;

                INSERT(tk);

            }

        }
        

    }
    else if(!strcmp(temp.lexeme,")")){
        printf("conversion");
        return 0;


    }
    else{
        printf("NOT VALID");
        return 0;

    }
}
int main()
{
    char c, buf[10];
    FILE *fp = fopen("digit.c", "r");
    c = fgetc(fp);
    if (fp == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }
    int row=0,column=0;
    // printf("sdf");
    Token retract;
    retract.row = 0;
    int countt =0;
    // while (retract.row !=-1)
    while(countt<6)
    {
        retract=getNextToken(c,fp,&row,&column);
        if(retract.type==DATATYPE){
            checkST(retract,c,fp,&row,&column);
        }
        printToken(retract);
        countt+=1;
        Display();
    }

    
}