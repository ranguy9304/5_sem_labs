#include <stdio.h>
# include<stdlib.h>
int main()
{
    FILE *fa, *fb,*ftemp;
    int ca, cb;
    fa = fopen("/home/cdlab/210905324_rudra/lab3/digit.c", "r");
    if (fa == NULL){
        printf("Cannot open file \n");
        exit(0); 
    }
    fb = fopen("testical.c", "w");
    ca = getc(fa);
    int first=2,count=0,found=0;
    while (ca != EOF)
    {
        first-=1;
        
        

        
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
            // first=1;
            cb = getc(fa);
            if (cb == '/')
            {
                while(ca != '\n')
                ca = getc(fa);
            }
            else if (cb == '*')
            {
                printf("det");
                // do
                // {
                while(ca != '*')
                    ca = getc(fa);
                ca = getc(fa);
                ca = getc(fa);
                // } while (ca != '/');
            }
            else
            {
                
                putc(ca,fb);
                putc(cb,fb);
            }
        }
        ftemp=fa;
        if (ca == '#' && count==0 )
        {   
            // printf("\n\n");
            fseek( fa, -2, SEEK_CUR );
            cb=getc(fa);
            // printf("%c",cb);
            while (cb==' ' || cb=='\n')
            {
                // printf("%c",cb);
                if (cb=='\n'){
                    found=1;
                    break;
                }
            
                if (cb==' '){
                    fseek( fa, -2, SEEK_CUR );
                    cb=getc(fa);
                    
                }
                else{
                    break;
                }
                /* code */
            }
            fa=ftemp;
            if (found==1 || first==1){
                
                while(ca != '\n' && ca !=EOF)
                ca = getc(fa);

            }
            
        }
        
     
        else {
            // first=1;
            
            // printf("%c",ca);
                if (ca == '\n'){
                    // first=0;

                }
            if(ca=='"' || '\''){
                if (count==1){
                    count-=1;
                }
                else if (count==0){
                    count+=1;
                }
            }
            putc(ca,fb);
            ftemp=fa;
        }
        ca = getc(fa);
        // first=0;
    }
    fclose(fa);
    fclose(fb);
    return 0;
}
