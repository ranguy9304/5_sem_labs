#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Token{
  int row;
  int column;
  char type[20];
} Token;
void printToken(Token t){
    printf("< %s , row : %d , column : %d >\n",t.type,t.row,t.column);
}
Token isOpp(char c,char * buf,FILE *fp,int i,int *row,int *column){

    if(c=='+'){
        buf[i++]=c;
        buf[i]='\0';
        c = fgetc(fp);
        if(c=='+'){
            buf[i++]=c;
            buf[i]='\0';
            // printf(" increment op : %s\n",buf);
            Token t;
            t.row=*row;
            
            t.column=*column;
            strcpy(t.type,buf);

            return t;

        }
        else{
            fseek( fp, -1, SEEK_CUR );
            // printf(" addition op : %s\n",buf);
            Token t;
            t.row=*row;
            t.column=*column;
            strcpy(t.type,buf);

            return t;

        }

    }
    else if(c=='-'){
        buf[i++]=c;
        buf[i]='\0';
        c = fgetc(fp);
        if(c=='-'){
            buf[i++]=c;
            buf[i]='\0';
            // printf(" decrement op : %s\n",buf);
            Token t;
            t.row=*row;
            
            t.column=*column;
            strcpy(t.type,buf);

            return t;

        }
        else{
            fseek( fp, -1, SEEK_CUR );
            // printf(" substraction op : %s\n",buf);
            Token t;
            t.row=*row;
            t.column=*column;
            strcpy(t.type,buf);

            return t;

        }

    }
    else if(c=='/'){
        buf[i++]=c;
        buf[i]='\0';
        
        
        // printf(" division op : %s\n",buf);
        Token t;
            t.row=*row;
            t.column=*column;
            strcpy(t.type,buf);

            return t;


    }
    else if(c=='*'){
        buf[i++]=c;
        buf[i]='\0';
        
        
        // printf(" mult op : %s\n",buf);
        Token t;
            t.row=*row;
            t.column=*column;
            strcpy(t.type,buf);

            return t;


    }
    else{
        Token t;
        t.row=-1;
        t.column=-1;
        strcpy(t.type,"");
        return t;
    }
    
}
Token isBracket(char c,char * buf,FILE *fp,int i,int *row,int *column){
    if( c=='['||c==']'||
        c=='{'||c=='}'||
        c=='('||c==')'){
            char bb[]={c,'\0'};


            // printf("bracket : %c\n",c);
            Token t;
            t.row=*row;
            t.column=*column;
            strcpy(t.type,bb);
            return t;

        }
        Token t;
        t.row=-1;
        t.column=-1;
        strcpy(t.type,"");
        return t;

}
Token isNum(char c,char * buf,FILE *fp,int i,int *row,int *column){
    int j=0;
    char temp[100];
    temp[j]='\0';
    if ((c>=48 && c<=57) || c==46 ){
         
   
    do
    {
        temp[j++]=c;
        temp[j]='\0';
        c = fgetc(fp);
        
    }while (c != EOF && ((c>=48 && c<=57) || c==46 ));
    
    fseek( fp, -1, SEEK_CUR );
	// printf("variable : %s\n",temp);
	Token t;
            t.row=*row;
            t.column=*column;
            strcpy(t.type,temp);
            return t;
    }
    else{
        Token t;
            t.row=-1;
            t.column=0;
            strcpy(t.type,"asd");
            return t;
    }
}
Token isWord(char c,char * buf,FILE *fp,int i,int *row,int *column){
    int j=0;
    char temp[100];
    temp[j]='\0';
    if ((c>=65 && c<=90) || (c>=97 && c<=122) || c==95 ){
         
   
    do
    {
        temp[j++]=c;
        temp[j]='\0';
        c = fgetc(fp);
        
    }while (c != EOF && ((c>=65 && c<=90) || (c>=97 && c<=122) || (c>=48 && c<=57) || c==95  ));
    if (!strcmp(temp, "if") || !strcmp(temp, "else") ||
		!strcmp(temp, "while") || !strcmp(temp, "do") ||
		!strcmp(temp, "break") ||
		!strcmp(temp, "continue") || !strcmp(temp, "int")
		|| !strcmp(temp, "double") || !strcmp(temp, "float")
		|| !strcmp(temp, "return") || !strcmp(temp, "char")
		|| !strcmp(temp, "case") || !strcmp(temp, "char")
		|| !strcmp(temp, "sizeof") || !strcmp(temp, "long")
		|| !strcmp(temp, "short") || !strcmp(temp, "typedef")
		|| !strcmp(temp, "switch") || !strcmp(temp, "unsigned")
		|| !strcmp(temp, "void") || !strcmp(temp, "static")
		|| !strcmp(temp, "struct") || !strcmp(temp, "goto")|| !strcmp(temp, "bool")){
            // printf("keyword : %s %d %d \n",temp,row,column);
            fseek( fp, -1, SEEK_CUR );
            Token t;
            t.row=*row;
            t.column=*column;
            strcpy(t.type,temp);
            // printToken(t);
            return t;
            

        }
        fseek( fp, -1, SEEK_CUR );
	// printf("variable : %s\n",temp);
	Token t;
            t.row=*row;
            t.column=*column;
            strcpy(t.type,temp);
            return t;
    }
    else{
        Token t;
            t.row=-1;
            t.column=0;
            strcpy(t.type,"asd");
            return t;
    }
}
Token isRopp(char c,char* buf,FILE *fp,int i,int *row,int *column){
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
            t.row=*row;
            
            t.column=*column;
            strcpy(t.type,buf);
            return t;
            }
            else
            {
                buf[i] = '\0';
                // printf("\n Assignment operator: %s\n", buf);
                fseek( fp, -1, SEEK_CUR );
                Token t;
            t.row=*row;
            t.column=*column;
            strcpy(t.type,buf);
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
                else{
                    fseek( fp, -1, SEEK_CUR );
                }
                buf[i] = '\0';
                // printf("\n Relational operator : %s\n", buf);
                Token t;
            t.row=*row;
            
            t.column=*column;
            strcpy(t.type,buf);
            return t;
            }
            else
            {
                buf[i] = '\0';
                Token t;
            t.row=-1;
            t.column=0;
            strcpy(t.type,"");
            return t;
            }
        }

}
Token getNextToken(char c,FILE *fp,int *row,int *column){
    // int row=0,column=0;
    char buf[10];
    Token retract;
    retract.row=-1;
    // printf("sdf");
    while (c != EOF && retract.row==-1)
    {
        
        if(c=='\n'){
            c = fgetc(fp);
            // printf("rn\n");
             if(c=='\n'){
                *row+=1;
                *column=0;

             }
            // continue;
        }
        
        
        
        int i = 0;
        buf[0] = '\0';
        retract=isNum(c,buf,fp,i,row,column);
        if(retract.row>=0){
            *column+=1;
            
            
            return retract;
        }
        retract=isWord(c,buf,fp,i,row,column);
        if(retract.row>=0){
            *column+=1;
            // printf("%d",*column);
            return retract;
        }
        retract=isRopp(c,buf,fp,i,row,column);
        
        if(retract.row>=0){
            *column+=1;
            return retract;
        }
        retract=isBracket(c,buf,fp,i,row,column);
        if(retract.row>=0){
            *column+=1;
            return retract;
        }
        retract =isOpp(c,buf,fp,i,row,column);
        if(retract.row>=0){
            *column+=1;
            return retract;
        }
        // if(c=='\n'){
        //     *row+=1;
        //     *column=0;
        //     // continue;
        // }

        
        c = fgetc(fp);
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
    printToken(getNextToken(c,fp,&row,&column));
    printToken(getNextToken(c,fp,&row,&column));
    printToken(getNextToken(c,fp,&row,&column));
    printToken(getNextToken(c,fp,&row,&column));

    
}