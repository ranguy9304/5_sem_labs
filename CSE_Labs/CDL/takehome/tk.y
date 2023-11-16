%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern FILE* yyin;
extern int yylex();

void yyerror(const char *s);
 
%}
 
%union {
    int intValue;
    char* strValue;
}
 
%token CLASS PUBLIC STATIC VOID INT BOOLEAN STRING IF ELSE WHILE FOR RETURN PRINT MAIN
%token IDENTIFIER INT_LITERAL BOOLEAN_LITERAL STRING_LITERAL
%token PLUS MINUS MULTIPLY DIVIDE EQUALS EQUALS_EQUALS NOT_EQUALS LESS_THAN GREATER_THAN LESS_EQUALS GREATER_EQUALS
%token LPAREN RPAREN LBRACE RBRACE SEMICOLON COMMA RBRACKET LBRACKET
 
%type <strValue> IDENTIFIER STRING_LITERAL
%type <intValue> INT_LITERAL BOOLEAN_LITERAL
 
%precedence LOWER_THAN_ELSE
%precedence ELSE
%left EQUALS_EQUALS NOT_EQUALS
%left LESS_THAN GREATER_THAN LESS_EQUALS GREATER_EQUALS
%left PLUS MINUS
%left MULTIPLY DIVIDE
%right EQUALS
 
%%
 
Program:
    ClassDeclarationList
    ;
ClassDeclarationList:
    /* empty */
    | ClassDeclaration ClassDeclarationList
    ;

ClassDeclaration:
    CLASS IDENTIFIER LBRACE ClassBody RBRACE
    ;

ClassBody:
    /* empty */
    | ClassMember ClassBody
    ;

ClassMember:
    VariableDeclaration
    | MethodDeclaration
    ;

VariableDeclaration:
    Type IDENTIFIER SEMICOLON
    ;

MethodDeclaration:
    PUBLIC STATIC VOID MAIN LPAREN STRING LBRACKET RBRACKET IDENTIFIER RPAREN LBRACE MethodBody RBRACE
    ;

MethodBody:
    StatementList
    ;

StatementList:
    /* empty */
    | Statement StatementList
    ;

Statement:
    ExpressionStatement
    | IfStatement
    | WhileStatement
    | ForStatement
    | PrintStatement
    | ReturnStatement
    | VariableDeclaration
    ;

ExpressionStatement:
    Expression SEMICOLON
    ;


WhileStatement:
    WHILE LPAREN Expression RPAREN Statement
    ;

ForStatement:
    FOR LPAREN ExpressionStatement ExpressionStatement Expression RPAREN Statement
    ;

PrintStatement:
    PRINT LPAREN Expression RPAREN SEMICOLON
    ;

ReturnStatement:
    RETURN Expression SEMICOLON
    ;
Expression:
    IDENTIFIER
    | Literal
    | Expression PLUS Expression
    | Expression MINUS Expression
    | Expression MULTIPLY Expression
    | Expression DIVIDE Expression
    | Expression EQUALS_EQUALS Expression
    | Expression NOT_EQUALS Expression
    | Expression LESS_THAN Expression
    | Expression GREATER_THAN Expression
    | Expression LESS_EQUALS Expression
    | Expression GREATER_EQUALS Expression
    | LPAREN Expression RPAREN
    | IDENTIFIER EQUALS Expression %prec EQUALS
    ;
 
IfStatement:
    IF LPAREN Expression RPAREN Statement %prec LOWER_THAN_ELSE
    | IF LPAREN Expression RPAREN Statement ELSE Statement
    ;


Literal:
    INT_LITERAL
    | BOOLEAN_LITERAL
    | STRING_LITERAL
    ;

Type:
    INT
    | BOOLEAN
    | STRING
    ;

%%
void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main() {
    printf("Starting the parser...\n");
    yyin = fopen("input.c","r");
    if (yyparse() == 0) {
        printf("Parsing complete!\n");
    } else {
        printf("Parsing failed.\n");
    }
    return 0;
}
