#include <stdio.h>
# include<stdlib.h>
int main()
{
    FILE *fa, *fb;
    int ca, cb;
    fa = fopen("test.c", "r");
    if (fa == NULL){
        printf("Cannot open file \n");
        exit(0); 
    }
    fb = fopen("testical.c", "w");
    ca = getc(fa);
    int first=0,count=0;
    while (ca != EOF)
    {
        
        if (ca == '#' && first==0 && count==0)
        {
            while(ca != '\n' && ca !=EOF)
            ca = getc(fa);
        }

        
        if(ca==' ')
        {
            // if(first==0){

            // first=0;
            // }
            // if(first==1){

            // first=1;
            // }
            putc(ca,fb);
            while(ca==' ')
            ca = getc(fa);
        }
        if (ca=='/')
        {   
            first=1;
            cb = getc(fa);
            if (cb == '/')
            {
                while(ca != '\n')
                ca = getc(fa);
            }
            else if (cb == '*')
            {
                do
                {
                while(ca != '*')
                    ca = getc(fa);
                ca = getc(fa);
                } while (ca != '/');
            }
            else
            {
                
                putc(ca,fb);
                putc(cb,fb);
            }
        }
     
        else {
            // first=1;
            
            printf("%c",ca);
                if (ca == '\n'){
                    first=0;

                }
            if(ca=='"'){
                if (count==1){
                    count-=1;
                }
                else if (count==0){
                    count+=1;
                }
            }
            putc(ca,fb);
        }
        ca = getc(fa);
        // first=0;
    }
    fclose(fa);
    fclose(fb);
    return 0;
}
