#include <stdio.h>
# inc
void func1();
void func2();
 
#pragma startup func1
// specifying funct2 to execute before end
    #pragma exit func2
 
void func1() { printf("Inside func\njbsdjfbsdhfsd1()\n"); }
 
void func2() { printf("Inside func2()\n"); }
 /*  dfgsdg   */

      #pragma exit func2
int main()
{
    void func1();
    void func2();
    printf("Inside main()\n");
 
    return 0;
}