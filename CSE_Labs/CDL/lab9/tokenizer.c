#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>



char *TokenType[] = {"OPP", "ROPP", "DATATYPE", "IDENTIFIER", "KEYWORD","NUMBER","NONE"};
enum TokenList
{
    OPP = 0,
    ROPP,
    DATATYPE,
    IDENTIFIER,
    KEYWORD,
    NUMBER,
    NONE
};
typedef struct Token
{
    int row;
    int column;
    char lexeme[20];
    enum TokenList type;
} Token;
Token *tokenIndexTable;
int noTokens=0;
int readTokenIndex=-1;
void printToken(Token t)
{
    printf("< %s , row : %d , column : %d , TokenType : %s >\n", t.lexeme, t.row, t.column,TokenType[t.type]);
}
Token isOpp(char c, char *buf, FILE *fp, int i, int *row, int *column)
{

    if (c == '+')
    {
        buf[i++] = c;
        buf[i] = '\0';
        c = fgetc(fp);
        if (c == '+')
        {
            buf[i++] = c;
            buf[i] = '\0';
            // printf(" increment op : %s\n",buf);
            Token t;
            t.row = *row;

            t.column = *column;
            strcpy(t.lexeme, buf);
            t.type = OPP;

            return t;
        }
        else
        {
            fseek(fp, -1, SEEK_CUR);
            // printf(" addition op : %s\n",buf);
            Token t;
            t.row = *row;
            t.column = *column;
            strcpy(t.lexeme, buf);
            t.type = OPP;

            return t;
        }
    }
    else if (c == '-')
    {
        buf[i++] = c;
        buf[i] = '\0';
        c = fgetc(fp);
        if (c == '-')
        {
            buf[i++] = c;
            buf[i] = '\0';
            // printf(" decrement op : %s\n",buf);
            Token t;
            t.row = *row;

            t.column = *column;
            strcpy(t.lexeme, buf);
            t.type = OPP;

            return t;
        }
        else
        {
            fseek(fp, -1, SEEK_CUR);
            // printf(" substraction op : %s\n",buf);
            Token t;
            t.row = *row;
            t.column = *column;
            strcpy(t.lexeme, buf);
            t.type = OPP;
            return t;
        }
    }
    else if (c == '/')
    {
        buf[i++] = c;
        buf[i] = '\0';

        // printf(" division op : %s\n",buf);
        Token t;
        t.row = *row;
        t.column = *column;
        strcpy(t.lexeme, buf);
        t.type = OPP;

        return t;
    }
    else if (c == '*')
    {
        buf[i++] = c;
        buf[i] = '\0';

        // printf(" mult op : %s\n",buf);
        Token t;
        t.row = *row;
        t.column = *column;
        strcpy(t.lexeme, buf);
        t.type = OPP;

        return t;
    }
    else
    {
        Token t;
        t.row = -1;
        t.column = -1;
        strcpy(t.lexeme, "");
        t.type=NONE;
        return t;
    }
}
Token isMyg(char c, char *buf, FILE *fp, int i, int *row, int *column)
{

    if (c == ';')
    {
        Token t;
        t.row = *row;
        t.column = *column;
        strcpy(t.lexeme, ";");
        t.type = NONE;

        return t;
    }
    else if (c == ',')
    {
        Token t;
        t.row = *row;
        t.column = *column;
        strcpy(t.lexeme, ",");
        t.type = NONE;

        return t;
    }
    
    else
    {
        Token t;
        t.row = -1;
        t.column = -1;
        strcpy(t.lexeme, "");
        t.type=NONE;
        return t;
    }
}
Token isBracket(char c, char *buf, FILE *fp, int i, int *row, int *column)
{
    if (c == '[' || c == ']' ||
        c == '{' || c == '}' ||
        c == '(' || c == ')')
    {
        char bb[] = {c, '\0'};

        // printf("bracket : %c\n",c);
        Token t;
        t.row = *row;
        t.column = *column;
        strcpy(t.lexeme, bb);
        t.type=NONE;
        return t;
    }
    Token t;
    t.row = -1;
    t.column = -1;
    strcpy(t.lexeme, "");
    t.type=NONE;
    return t;
}
Token isNum(char c, char *buf, FILE *fp, int i, int *row, int *column)
{
    int j = 0;
    char temp[100];
    temp[j] = '\0';
    if ((c >= 48 && c <= 57) || c == 46)
    {

        do
        {
            temp[j++] = c;
            temp[j] = '\0';
            c = fgetc(fp);

        } while (c != EOF && ((c >= 48 && c <= 57) || c == 46));

        fseek(fp, -1, SEEK_CUR);
        // printf("variable : %s\n",temp);
        Token t;
        t.row = *row;
        t.column = *column;
        strcpy(t.lexeme, temp);
        t.type=NUMBER;
        return t;
    }
    else
    {
        Token t;
        t.row = -1;
        t.column = 0;
        strcpy(t.lexeme, "asd");
        t.type=NONE;
        return t;
    }
}
Token isWord(char c, char *buf, FILE *fp, int i, int *row, int *column)
{
    int j = 0;
    char temp[100];
    temp[j] = '\0';
    if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || c == 95)
    {

        do
        {
            temp[j++] = c;
            temp[j] = '\0';
            c = fgetc(fp);

        } while (c != EOF && ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c >= 48 && c <= 57) || c == 95));
        if (!strcmp(temp, "if") || !strcmp(temp, "else") ||
            !strcmp(temp, "while") || !strcmp(temp, "do") ||
            !strcmp(temp, "break") ||
            !strcmp(temp, "continue") || !strcmp(temp, "static") || !strcmp(temp, "struct") || !strcmp(temp, "goto") || !strcmp(temp, "bool"))
        {
            // printf("keyword : %s %d %d \n",temp,row,column);
            fseek(fp, -1, SEEK_CUR);
            Token t;
            t.row = *row;
            t.column = *column;
            strcpy(t.lexeme, temp);
            t.type=KEYWORD;
            // printToken(t);
            return t;
        }
        if ( !strcmp(temp, "int") || !strcmp(temp, "double") || !strcmp(temp, "float") || !strcmp(temp, "return") || !strcmp(temp, "char") || !strcmp(temp, "case") || !strcmp(temp, "char") || !strcmp(temp, "sizeof") || !strcmp(temp, "long") || !strcmp(temp, "short") || !strcmp(temp, "lexemedef") || !strcmp(temp, "switch") || !strcmp(temp, "unsigned") || !strcmp(temp, "void") )
        {
            // printf("keyword : %s %d %d \n",temp,row,column);
            fseek(fp, -1, SEEK_CUR);
            Token t;
            t.row = *row;
            t.column = *column;
            strcpy(t.lexeme, temp);
            t.type=DATATYPE;
            // printToken(t);
            return t;
        }
        fseek(fp, -1, SEEK_CUR);
        // printf("variable : %s\n",temp);
        Token t;
        t.row = *row;
        t.column = *column;
        strcpy(t.lexeme, temp);
        t.type=IDENTIFIER;
        return t;
    }
    else
    {
        Token t;
        t.row = -1;
        t.column = 0;
        strcpy(t.lexeme, "asd");
        t.type=NONE;
        return t;
    }
}
Token isRopp(char c, char *buf, FILE *fp, int i, int *row, int *column)
{
    if (c == '=')
    {
        buf[i++] = c;
        c = fgetc(fp);
        if (c == '=')
        {
            buf[i++] = c;
            buf[i] = '\0';
            // printf("\n Relational operator : %s\n", buf);
            Token t;
            t.row = *row;

            t.column = *column;
            strcpy(t.lexeme, buf);
            t.type=ROPP;
            return t;
        }
        else
        {
            buf[i] = '\0';
            // printf("\n Assignment operator: %s\n", buf);
            fseek(fp, -1, SEEK_CUR);
            Token t;
            t.row = *row;
            t.column = *column;
            strcpy(t.lexeme, buf);
            t.type=ROPP;
            return t;
        }
    }
    else
    {
        if (c == '<' || c == '>' || c == '!')
        {
            buf[i++] = c;
            c = fgetc(fp);
            if (c == '=')
            {
                buf[i++] = c;
            }
            else
            {
                fseek(fp, -1, SEEK_CUR);
            }
            buf[i] = '\0';
            // printf("\n Relational operator : %s\n", buf);
            Token t;
            t.row = *row;

            t.column = *column;
            strcpy(t.lexeme, buf);
            t.type=ROPP;
            return t;
        }
        else
        {
            buf[i] = '\0';
            Token t;
            t.row = -1;
            t.column = 0;
            strcpy(t.lexeme, "");
            t.type=NONE;
            return t;
        }
    }
}
Token getNextToken(char c, FILE *fp, int *row, int *column)
{
    // int row=0,column=0;
    char buf[10];
    Token retract;
    retract.row = -1;
    // printf("sdf");
    while (c != EOF && retract.row == -1)
    {

        if (c == '\n')
        {
            c = fgetc(fp);
            // printf("rn\n");
            if (c == '\n')
            {
                *row += 1;
                *column = 0;
            }
            // continue;
        }

        int i = 0;
        buf[0] = '\0';
        retract = isNum(c, buf, fp, i, row, column);
        if (retract.row >= 0)
        {
            *column += 1;

            return retract;
        }
        retract = isWord(c, buf, fp, i, row, column);
        if (retract.row >= 0)
        {
            *column += 1;
            // printf("%d",*column);
            return retract;
        }
        retract = isRopp(c, buf, fp, i, row, column);

        if (retract.row >= 0)
        {
            *column += 1;
            return retract;
        }
        retract = isBracket(c, buf, fp, i, row, column);
        if (retract.row >= 0)
        {
            *column += 1;
            return retract;
        }
        retract = isOpp(c, buf, fp, i, row, column);
        if (retract.row >= 0)
        {
            *column += 1;
            return retract;
        }
        retract = isMyg(c, buf, fp, i, row, column);
        if (retract.row >= 0)
        {
            *column += 1;
            return retract;
        }
        // if(c=='\n'){
        //     *row+=1;
        //     *column=0;
        //     // continue;
        // }

        c = fgetc(fp);
    }
    retract.row = -1;
    return retract;
}


void storeTokens(char c, FILE *fp, int *row, int *column){
    Token retract;
    retract.row = 0;
    noTokens=0;
    tokenIndexTable = (Token *)malloc(sizeof(Token));
    while (retract.row !=-1){
        noTokens++;
        retract=getNextToken(c,fp,row,column);
        // printToken(retract);
        tokenIndexTable = (Token *)realloc(tokenIndexTable,sizeof(Token) * noTokens);
        tokenIndexTable[noTokens-1]=retract;
        
    }
}
void printTokenIndexTable(){
    for(int i=0;i<noTokens;i++){
        printToken(tokenIndexTable[i]);
    }
}


Token getNextTokenTable(){
    if(readTokenIndex == noTokens-1)
    {
        printf("LAST TOKEN REACHED\n");
        exit(0);
        return tokenIndexTable[readTokenIndex];
        

    }
    // Token retract =
    // printToken(retract);
    return tokenIndexTable[++readTokenIndex];
    
}
Token getPrevTokenTable(){
    if(readTokenIndex == 0 ){
        printf("FIRST TOKEN REACHED\n");
        return tokenIndexTable[readTokenIndex];
    }
    return tokenIndexTable[--readTokenIndex];
    
}
Token getCurTokenTable(){
    return tokenIndexTable[readTokenIndex];
    
}
// int main()
// {
//     char c, buf[10];
//     FILE *fp = fopen("digit.c", "r");
//     c = fgetc(fp);
//     if (fp == NULL)
//     {
//         printf("Cannot open file \n");
//         exit(0);
//     }
//     int row=0,column=0;
//     // printf("sdf");
//     Token retract;
//     retract.row = 0;
    
//     while (retract.row !=-1){
//         retract=getNextToken(c,fp,&row,&column);
//         printToken(retract);
//     }
//     // printToken(getNextToken(c,fp,&row,&column));
//     // printToken(getNextToken(c,fp,&row,&column));
//     // printToken(getNextToken(c,fp,&row,&column));
//     // printToken(getNextToken(c,fp,&row,&column));

// }