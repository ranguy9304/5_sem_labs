#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "symbolTable.c"
#include "tokenizer.c"
#include "preprocessor.c"

#define max 20

// program - > main ( ) { declaration stat-list }                 FI = { main }   FO = { $ }
// id-list -> id idPrime                                            FI ={ id }   FO ={ $ }
// idPrime -> epislon | , id-list | [number],id-list | [number]     FI = { $ , , , [  } FO ={ $ }
// stat-list -> stat stat-list | epislon                            FI = { id , $ } FO = { } }
// stat -> ass-stat ;                                               FI = { id }  FO = { id, $ }
// ass-stat -> id = expn                                            FI = { id }  FO = { ; }
// expn -> simp-exp eprime                                          FI = { id , num } FO = { ; }
// eprime -> relop simp_exp | epsilon                               FI = { relop , $ } FO = { ; }
// simp-exp -> term seprime                                         FI = { id , num }
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
bool id_list();
char error[100];
void saveError(char *str)
{
    // printf("ERROR : %s \n", str);
    strcpy(error, str);
}
void invalid()
{
    printf("Parse Unsuccessful\n");
    retract = getPrevTokenTable();
    printToken(retract);
    printf("Error at row %d and column %d\n", retract.row, retract.column);
    printf("ERROR : %s\n", error);
}

// bool id_list();
bool listPrime()
{
    printf("list prime\n");
    // checkpoint = *fp;

    if (strcmp(getNextTokenTable().lexeme, ",") == 0)
    {
        id_list();
        return true;
    }
    else if (strcmp(getCurTokenTable().lexeme, "[") == 0)
    {
        printf("[ def entry\n");
        if (getNextTokenTable().type == NUMBER)
        {

            if (strcmp(getNextTokenTable().lexeme, "]") == 0)
            {
                printf("] def entry\n");
                if (strcmp(getNextTokenTable().lexeme, ",") == 0)
                {
                    // printToken(getCurTokenTable());
                    id_list();
                    return true;
                }
                else
                {
                    printf("returning from listPrime\n");
                    getPrevTokenTable();
                    return true;
                }
            }
            else
            {
                saveError("no  ]");
                return false;
            }
        }

        else
        {
            saveError("for now number in []");
            return false;
        }
    }
    else
    {
        // printToken(getCurTokenTable());
        saveError("no , or [");

        return false;
    }
    // *fp = checkpoint;
}
bool id_list()
{
    printf("id list\n");

    if (getNextTokenTable().type == IDENTIFIER)
    {
        printf("enter into id_list\n");
        listPrime();
        return true;
    }
    saveError("not an identifier");
    return false;
}

// bool assignPrime()
// {

//     retract.row = 0;
//     // retract = ;
//     if (getNextTokenTable().type == IDENTIFIER)
//     {
//         // retract = getNextTokenTable();
//         if (strcmp(getNextTokenTable().lexeme, ";") == 0)
//             return;
//     }
//     else if (retract.type == NUMBER)
//     {
//         // retract = getNextTokenTable();
//         if (strcmp(getNextTokenTable().lexeme, ";") == 0)
//             return;
//     }
//     else
//     {
//         invalid();
//         exit(0);
//     }
// }
// bool Assignment()
// {

//     retract.row = 0;

//     if (getNextTokenTable().type == IDENTIFIER)
//     {

//         if (strcmp(getNextTokenTable().lexeme, "=") == 0)
//             assignPrime();
//         else
//         {

//             invalid();
//             exit(0);
//         }
//     }
// }

bool data_type()
{
    printf("data type\n");

    retract = getNextTokenTable();

    if (strcmp(retract.lexeme, "int") == 0 || strcmp(retract.lexeme, "char") == 0)
        return true;
    else
    {
        getPrevTokenTable();
        saveError("not a datatype");
        return false;
        // decl_flag = 0;
    }
}
bool decleration()
{
    printf("declaration\n");

    if (data_type())
        if (id_list())
        {
            if (!strcmp(getNextTokenTable().lexeme, ";"))
            {
                printf("decleration -> data_type id_list ;\n");
                decleration();
                return true;
            }
        }

    getPrevTokenTable();
    return true;
    // else
}
// factor -> id | num
bool factor()
{
    // printToken(getCurTokenTable());
    printf("factor ->\n");
    if (getNextTokenTable().type == IDENTIFIER)
    {
        printf("id");
        return true;
    }
    else
    {
        getPrevTokenTable();
        if (getNextTokenTable().type == NUMBER)
        {
            printf("NUM");
            return true;
        }
        else
        {
            getPrevTokenTable();
            saveError("should be number or id");
            return false;
        }
    }
}
// tprime -> mulop factor tprime | epsilon
bool tprime()
{
    printf("tprime\n");
    if (getNextTokenTable().type == OPP)
    {

        if (factor())
            tprime();
    }
    else
        getPrevTokenTable();
    return true;
}

// relop -> == | != | <= | >= | > | <
// addop -> + | -
// mulop -> * | / | %

// term -> factor tprime
bool term()
{
    printf("term\n");
    if (factor())
        if (tprime())
            return true;
    return false;
}
// seprime -> addop term seprime | epsilon
bool seprime()
{
    printf("seprime\n");
    if (getNextTokenTable().type == OPP)
    {

        if (term())
            seprime();
    }
    else
        getPrevTokenTable();

    return true;
}
// simp-exp -> term seprime
bool simp_exp()
{
    printf("simp exp\n");

    if (term())
        if (seprime())
            return true;
    return false;
}
// eprime -> relop simp_exp | epsilon
bool eprime()
{
    printf("eprime\n");
    if (getNextTokenTable().type == ROPP)
    {
        simp_exp();
    }
    else
        getPrevTokenTable();
    return true;
}

// expn -> simp-expn eprime
bool expn()
{
    printf("expn\n");
    if (simp_exp())
        if (eprime())
            return true;
    return false;
}
// ass-stat -> id = expn
bool ass_stat()
{
    printf("ass stat\n");

    if (getNextTokenTable().type == IDENTIFIER)
    {
        // printToken(getCurTokenTable());
        printf("ass-stat -> id\n");
        if (!strcmp(getNextTokenTable().lexeme, "="))
        {
            printf("ass-stat -> id =\n");
        }
        else
        {
            getPrevTokenTable();
            saveError("= not found");
            return false;
            // invalid();
            // exit(0);
        }
        if (expn())
            return true;
    }
    else
    {
        getPrevTokenTable();
        saveError("not id ");
        // invalid(0);
        return false;
    }
}
// stat -> ass-stat ;
bool stat()
{
    printf("stat\n");
    if (ass_stat())
    {
        if (!strcmp(getNextTokenTable().lexeme, ";"))
            return true;
        saveError("; not found");
        getPrevTokenTable();
    }
    // getPrevTokenTable();
    return false;
}
// stat-list -> stat stat-list | epislon
bool stat_list()
{
    printf("stat list\n");
    if (stat())
    {
        stat_list();
    }
    // else
    // {
    // printToken(getCurTokenTable());
    // printf("epsilon\n");
    // return false;
    // }
    return true;
}
// program - > main ( ) { declaration statment-list }
bool program()
{
    printf("program\n");

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
                    printf("going in\n");
                    if (!decleration())
                        return false;
                    if (!stat_list())
                        return false;

                    // printToken(getNextTokenTable());
                    if (strcmp(getNextTokenTable().lexeme, "}") == 0)
                    {
                        printf("Parse Successful");
                        return true;
                    }
                    else
                    {
                        if (!error )
                            saveError("missing }");
                        return false;
                    }
                }
                else
                {
                    saveError("no opening { ");
                    return false;
                }
            }
            else
            {
                saveError("no closing ) ");
                return false;
            }
        }
        else
        {
            saveError("no opening ( ");
            return false;
        }
    }
    else
    {
        saveError("no main ");
        return false;
    }
}

int main()
{
    struct ListElement *TABLE[TableLength];
    Initialize(TABLE);
    preprocessor("digit.c");
    fp = fopen(intermediateFilePath, "r");
    c = fgetc(fp);
    if (fp == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }
    storeTokens(c, fp, &row, &column);
    // printTokenIndexTable();
    if (!program())
    {
        invalid();
    }
}