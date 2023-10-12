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
bool DEBUG = false;
bool TESTING = false;
char c, buf[10];
int row = 0, column = 0;
FILE *fp, checkpoint;
Token retract;
// retract.row = 0;
int decl_flag = 1;
bool id_list();
char error[100];
bool errorOccoured = false;
void clearError()
{
    printf("error cleared\n");
    errorOccoured = false;
}

void saveError(char *str)
{
    if (1)
    {
        printf("\n#################### ERROR OCCOURED ####################\n\n");
        printf("ERROR : %s \n", str);
        printf("\n#################### -------------- ####################\n\n");
    }
    if (!errorOccoured)
    {
        errorOccoured = true;
        strcpy(error, str);
    }
}
void invalid()
{
    printf("\n############ PARSE UNSUCCESSFULL ############\n\n");
    retract = getPrevTokenTable();

    printf("$ ERROR AT ROW : %d , COLUMN : %d\n$ ", retract.row, retract.column);
    printToken(retract);
    printf("$ !!! %s !!! \n", error);
    printf("\n############ ------------------- ############\n\n");
}
void parseSuccess()
{
    printf("\n#################### PARSE SUCCESS ####################\n\n");
    // invalid();
    printf("\n#################### -------------- ####################\n\n");
}
// bool id_list();
bool listPrime()
{
    if (DEBUG)
        printf("list prime\n");
    // checkpoint = *fp;

    if (strcmp(getNextTokenTable().lexeme, ",") == 0)
    {
        id_list();
        return true;
    }
    else if (strcmp(getCurTokenTable().lexeme, "[") == 0)
    {

        if (getNextTokenTable().type == NUMBER)
        {

            if (strcmp(getNextTokenTable().lexeme, "]") == 0)
            {

                if (strcmp(getNextTokenTable().lexeme, ",") == 0)
                {
                    // printToken(getCurTokenTable());
                    id_list();
                    return true;
                }
                else
                {

                    getPrevTokenTable();

                    return true;
                }
            }
            else
            {
                saveError("[ ] OPENED BUT NOT CLOSED");
             
                return true;
            }
        }

        else
        {
            saveError("NO NUMBER AFTER [ ");
          
            return true;
        }
    }
    else
    {
        // printToken(getCurTokenTable());
        // saveError("no , or [");
        getPrevTokenTable();
        return true;
    }
    // *fp = checkpoint;
}
bool id_list()
{
    if (DEBUG)
        printf("id list\n");

    if (getNextTokenTable().type == IDENTIFIER)
    {
        listPrime();
        return true;
    }
    saveError("NOT AN IDENTIFIER");
    getPrevTokenTable();
    if (TESTING)
    {
        invalid();
        exit(0);
    }
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
    if (DEBUG)
        printf("data type\n");

    retract = getNextTokenTable();

    if (strcmp(retract.lexeme, "int") == 0 || strcmp(retract.lexeme, "char") == 0)
        return true;
    else
    {

        getPrevTokenTable();
        saveError("NOT A DATATYPE");
        if (TESTING)
        {
          
        }
        return false;
        // decl_flag = 0;
    }
}
bool decleration()
{
    if (DEBUG)
        printf("declaration\n");

    if (data_type())
        if (id_list())
        {
            if (!strcmp(getNextTokenTable().lexeme, ";"))
            {

                decleration();
                // clearError();
                return true;
            }
        }

    // getPrevTokenTable();
    return true;
    // else
}
// factor -> id | num
bool factor()
{
    // printToken(getCurTokenTable());
    if (DEBUG)
        printf("factor ->\n");
    if (getNextTokenTable().type == IDENTIFIER)
    {
        return true;
    }
    else
    {
        getPrevTokenTable();
        if (getNextTokenTable().type == NUMBER)
        {
            return true;
        }
        else
        {
            getPrevTokenTable();
            saveError("SHOULD BE ID OR NUMBER");
            if (TESTING)
            {
                invalid();
                exit(0);
            }
            return false;
        }
    }
}
// tprime -> mulop factor tprime | epsilon
bool tprime()
{
    if (DEBUG)
        printf("tprime\n");
    if (!strcmp(getNextTokenTable().lexeme,"*" ) || !strcmp(getCurTokenTable().lexeme,"/" ))
    {

        if (factor())
            tprime();
    }
    else
    {
        saveError("MUL OPP NOT FOUND");

        getPrevTokenTable();
    }
    return true;
}

// relop -> == | != | <= | >= | > | <
// addop -> + | -
// mulop -> * | / | %

// term -> factor tprime
bool term()
{
    if (DEBUG)
        printf("term\n");
    if (factor())
        if (tprime())
            return true;
    if (TESTING)
    {
        invalid();
        exit(0);
    }
    return false;
}
// seprime -> addop term seprime | epsilon
bool seprime()
{
    if (DEBUG)
        printf("seprime\n");
    if ((!strcmp(getNextTokenTable().lexeme,"+" ) )|| (!strcmp(getCurTokenTable().lexeme,"-" )))
    {

        if (term())
            seprime();
    }
    else
    {
        saveError("ADDOP NOT FOUND");
        // exit(0);
        getPrevTokenTable();
    }

    return true;
}
// simp-exp -> term seprime
bool simp_exp()
{
    if (DEBUG)
        printf("simp exp\n");

    if (term())
        if (seprime())
            return true;
    if (TESTING)
    {
        invalid();
        exit(0);
    }
    return false;
}
// eprime -> relop simp_exp | epsilon
bool eprime()
{
    if (DEBUG)
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
    if (DEBUG)
        printf("expn\n");
    if (simp_exp())
        if (eprime())
            return true;
    if (TESTING)
    {
        invalid();
        exit(0);
    }
    return false;
}
// ass-stat -> id = expn
bool ass_stat()
{
    if (DEBUG)
        printf("ass stat\n");

    if (getNextTokenTable().type == IDENTIFIER)
    {
        // printToken(getCurTokenTable());
        // printf("ass-stat -> id\n");
        if (!strcmp(getNextTokenTable().lexeme, "="))
        {
            // printf("ass-stat -> id =\n");
        }
        else
        {
            getPrevTokenTable();
            getPrevTokenTable();
            saveError("= NOT PRESENT");
            if (TESTING)
            {
                invalid();
                exit(0);
            }
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
        saveError("NOT ID");
        // invalid(0);
        if (TESTING)
        {
            invalid();
            exit(0);
        }
        return false;
    }
}
// stat -> ass-stat ;
bool stat()
{
    if (DEBUG)
        printf("stat\n");
    if (ass_stat())
    {
        if (!strcmp(getNextTokenTable().lexeme, ";"))
            return true;
        saveError("; not found");
        getPrevTokenTable();
    }
    // getPrevTokenTable();
    if (TESTING)
    {
        invalid();
        exit(0);
    }
    return false;
}
// stat-list -> stat stat-list | epislon
bool stat_list()
{
    if (DEBUG)
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
    if (DEBUG)
        printf("program -> ");

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

                    if (!decleration())
                        return false;
                    if (!stat_list())
                        return false;

                    // printToken(getNextTokenTable());
                    if (strcmp(getNextTokenTable().lexeme, "}") == 0)
                    {
                        parseSuccess();
                        return true;
                    }
                    else
                    {
                        if (!error)
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
    fp = fopen("digit.c", "r");
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
