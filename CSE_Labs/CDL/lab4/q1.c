#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "symbolTable.c"
#include "tokenizer.c"

char * capitalizeString(char *str) {
    // Check if the input string is not empty
    if (str == NULL || *str == '\0') {
        return str;
    }
    
    // Capitalize the first character
    *str = toupper(*str);
    
    // Iterate through the rest of the string and capitalize subsequent letters
    int count=sizeof(str)/sizeof(str[0]);
    // printf("%d",count);
    for (int i = 1;str[i]!='\0'; i++) {
        // printf("%c",str[i]);
        
        str[i] = toupper(str[i]);
        // printf("%c",str[i]);
   
        }
    
    return str;
}


int checkST(Token tk,char c, FILE *fp, int *row, int *column){
    Token temp;
    // char temp11=[0];
    enum dataType contextType=enumString(capitalizeString(tk.lexeme));
    temp=getNextToken(c,fp,row,column);
    printToken(temp);
    char tempIdentifierHolder[40];
    if(temp.type==IDENTIFIER){
        strcpy(tempIdentifierHolder,temp.lexeme);
        temp=getNextToken(c,fp,row,column);
        printToken(temp);
        if(!strcmp(temp.lexeme,"(")){
            if(!SEARCH(tempIdentifierHolder)){
                struct TableToken tk;
                tk.lexeme=(char *)malloc(sizeof(char)*40);
                strcpy(tk.lexeme,tempIdentifierHolder);
                int tempargscount=0;
                
                while(strcmp(temp.lexeme,")")){
                temp=getNextToken(c,fp,row,column);
                if(temp.type==IDENTIFIER){
                    strcpy(tempIdentifierHolder,temp.lexeme);
                    // temp=getNextToken(c,fp,row,column);
             
                    if(!SEARCH(tempIdentifierHolder)){
                        struct TableToken tk;
                        tk.lexeme=(char *)malloc(sizeof(char)*40);
                        strcpy(tk.lexeme,tempIdentifierHolder);
                    
                        tempargscount+=1;

                    }

                }

            }
            tk.argsCount=tempargscount;
            tk.dataType=NONEDT;
            tk.index=-1;
            tk.returnType=contextType;

            INSERT(tk);
        }
        }
        else if(!strcmp(temp.lexeme,"=") || !strcmp(temp.lexeme,",")){
            // temp=getNextToken(c,fp,row,column);
            // printToken(temp);
            // temp=getNextToken(c,fp,row,column);
            // printToken(temp);
            while(strcmp(temp.lexeme,";")){
                if(temp.type==IDENTIFIER){
                    strcpy(tempIdentifierHolder,temp.lexeme);
                    // temp=getNextToken(c,fp,row,column);
             
                    if(!SEARCH(tempIdentifierHolder)){
                        struct TableToken tk;
                        tk.lexeme=(char *)malloc(sizeof(char)*40);
                        strcpy(tk.lexeme,tempIdentifierHolder);
                    
                        tk.argsCount=0;
                        tk.dataType=contextType;
                        tk.index=-1;
                        tk.returnType=NONEDT;

                        INSERT(tk);

                    }

                    
                }
                else if (!strcmp(temp.lexeme,"=") ){
                    if(!SEARCH(tempIdentifierHolder)){
                    struct TableToken tk;
                    tk.lexeme=(char *)malloc(sizeof(char)*40);
                    strcpy(tk.lexeme,tempIdentifierHolder);
                
                    tk.argsCount=0;
                    tk.dataType=contextType;
                    tk.index=-1;
                    tk.returnType=NONEDT;

                    INSERT(tk);

                    }

                }
                else if (!strcmp(temp.lexeme,",") ){
            
                    if(!SEARCH(tempIdentifierHolder)){
                    struct TableToken tk;
                    tk.lexeme=(char *)malloc(sizeof(char)*40);
                    strcpy(tk.lexeme,tempIdentifierHolder);
                
                    tk.argsCount=0;
                    tk.dataType=contextType;
                    tk.index=-1;
                    tk.returnType=NONEDT;

                    INSERT(tk);
                    }

                }

            temp=getNextToken(c,fp,row,column);
            // printToken(temp);

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
        printToken(retract);
        if(retract.type==DATATYPE){
            checkST(retract,c,fp,&row,&column);
        }
        countt+=1;
        // Display();
    }
    Display();

    
}