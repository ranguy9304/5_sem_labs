#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TableLength 30
enum dataType
{
    INT = 0,
    FLOAT,
    CHAR,
    DOUBLE,
    NONEDT

};
char *dataTypeString[] = {"INT",
                          "FLOAT",
                          "CHAR",
                          "DOUBLE",
                          "NONE"};
struct TableToken
{
    char *lexeme;
    int index;
    enum dataType returnType;
    enum dataType dataType; // row number, column number.
    int argsCount;
    struct ListElement *LOCALTABLE[TableLength];
};
struct ListElement
{
    struct TableToken tok;
    struct ListElement *next;
};

int enumString(char *str)
{
    puts(str);
    if (!strcmp(str, "INT"))
    {
        // printf("1");
        return INT;
    }
    else if (!strcmp(str, "DOUBLE"))
    {
        // printf("2");
        return DOUBLE;
    }
    else if (!strcmp(str, "FLOAT"))
    {
        // printf("3");
        return FLOAT;
    }
    else if (!strcmp(str, "CHAR"))
    {
        // printf("4");
        return CHAR;
    }
    else if (!strcmp(str, "NONEDT"))
    {
        // printf("4");
        return NONEDT;
    }
}
void Initialize(struct ListElement *TABLE[TableLength])
{
    for (int i = 0; i < TableLength; i++)
    {
        TABLE[i] = NULL;
    }
}
void Display(struct ListElement *TABLE[TableLength])
{
    // iterate through the linked list and display
    for (int i = 0; i < TableLength; i++)
    {
        if (TABLE[i] == NULL)
        {
            // printf("[ %d ] : NULL\n",i);
            // return ;
        }
        else
        {
            struct ListElement *ele = TABLE[i];
            while (ele != NULL)
            {
                printf("[ %d ] : < INDEX : %d, LEXEME : %s , RETURN : %s , DATATYPE : %s, ARGCOUNT : %d>\n", i, ele->tok.index, ele->tok.lexeme, dataTypeString[ele->tok.returnType], dataTypeString[ele->tok.dataType], ele->tok.argsCount);
                for (int i = 0; i < TableLength; i++)
                {
                    if (ele->tok.LOCALTABLE[i] == NULL)
                    {
                        // printf("[ %d ] : NULL\n",i);
                        // return ;
                    }
                    else
                    {
                        struct ListElement *ele2 = ele->tok.LOCALTABLE[i];
                        while (ele2 != NULL)
                        {
                            // printf("something->>>> \n");
                            printf("\t [ %d ] : < INDEX : %d, LEXEME : %s , RETURN : %s , DATATYPE : %s, ARGCOUNT : %d>\n", i, ele2->tok.index, ele2->tok.lexeme, dataTypeString[ele2->tok.returnType], dataTypeString[ele2->tok.dataType], ele2->tok.argsCount);
                            ele2 = ele2->next; // Add the element at the End in the case of a
                            // collision.
                        }
                    }
                }
                ele = ele->next; // Add the element at the End in the case of a
                // collision.
            }
        }
    }
}
int HASH(char *str)
{
    int sum = 0;
    char c = str[0];
    int count = 0;
    while (c != '\0')
    {
        count += 1;
        sum += c;
        c = str[count];
    }
    return sum % TableLength;
    // Develop an OpenHash function on a string.
}
int SEARCH(char *str, struct ListElement *TABLE[TableLength])
{
    int val = HASH(str);
    if (TABLE[val] == NULL)
    {
        // printf("search print");
        return 0;
    }
    else
    {
        struct ListElement *ele = TABLE[val];
        while (ele != NULL)
        {
            if (!strcmp(ele->tok.lexeme, str))
            {
                return 1;
            }
            ele = ele->next; // Add the element at the End in the case of a
            // collision.
        }
    }

    // Write a search routine to check whether a lexeme exists in the Symbol table.
    // Returns 1, if lexeme is found
    // else returns 0
}
void INSERT(struct TableToken tk, struct ListElement *TABLE[TableLength])
{
    if (SEARCH(tk.lexeme, TABLE) == 1)
    {

        printf("VALUE ALREADY EXIITS\n");
        return; // Before inserting we check if the element is present already.
    }
    int val = HASH(tk.lexeme);
    // printf("hash print-- %d",val);
    struct ListElement *cur = (struct ListElement *)malloc(sizeof(struct
                                                                  ListElement));
    cur->tok = tk;
    // Initialize(cur->tok.LOCALTABLE);
    cur->next = NULL;
    if (TABLE[val] == NULL)
    {
        TABLE[val] = cur; // No collosion.
    }
    else
    {
        struct ListElement *ele = TABLE[val];
        while (ele->next != NULL)
        {
            ele = ele->next; // Add the element at the End in the case of a
            // collision.
        }
        ele->next = cur;
    }
}
// int main()
// {
//     /* code */
//     // printf("hello");
    
//     Initialize(TABLE);
//     // printf("hello");
//     struct TableToken temp;
//     // printf("hello");
//     char buf[] = "INT";
//     temp.lexeme = buf;
//     // printf("hello");
//     temp.argsCount = 1;
//     temp.dataType = enumString(buf);
//     temp.returnType = enumString(buf);
//     temp.index = 1;
//     // printf("hello");
//     INSERT(temp, TABLE);

//     Display(TABLE);

//     return 0;
// }