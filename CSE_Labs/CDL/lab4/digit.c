
int b(dfsd,sdd){
    int fun=0;

}
    if (c == '=')
        {
            buf[i++] = c;
            c = fgetc(fp);
            if (c == '=')
            {
                buf[i++] = c;
                buf[i] = '\0';
                printf("\n Relational operator : %s\n", buf);
                return true;
            }
            else
            {
                buf[i] = '\0';
                printf("\n Assignment operator: %s\n", buf);
                return true;
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
                buf[i] = '\0';
                printf("\n Relational operator : %s\n", buf);
                return true;
            }
            else
            {
                buf[i] = '\0';
                buf(qwe,sdf)
                return false;
            }
        }

}
char* getNextToken(char c,FILE *fp){
    char buf[10];
    bool retract =false;
    while (c != EOF && !retract)
    {
        int i = 0;
        buf[0] = '\0';
        retract=isOpp(c,buf,fp,i);
        if(retract){
            return;
        }
        // retract=isWord(c,buf,fp,i);
        // if(retract){
        //     return;
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
    // getNextToken(c,fp);
    // getNextToken(c,fp);
    
}