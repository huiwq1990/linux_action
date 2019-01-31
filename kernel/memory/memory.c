#include <stdio.h>
#include <malloc.h>
#include <unistd.h>
// gcc memory.c -o mm
int bss_var;
int data_var0=1;
int main(int argc,char **argv)
{
    printf("below are addresses of types of process's mem\n");
    printf("text location:\n");
    printf("\t address of main(Code Segment):%p\n",main);
    printf("______________\n");
    int stack_var0=2;
    printf("Stack Location:\n");
    printf("\tInitial end of stack:%p\n",&stack_var0 );
     int stack_var1=3;
         printf("\tnew end of stack:%p\n",&stack_var1);
    printf("______________\n");

    printf("Data Location:\n");
        printf("\tAddress of data_var(Data Segment):%p\n",&data_var0);

static int data_var1= 4;
printf("\tNew end of data_var(Data Segment):%p\n",&data_var1);

    printf("______________\n");



    printf("BSS Location\n");

        printf("\tAddress of bss_var:%p\n",&bss_var);
    printf("______________\n");

char *b = sbrk((ptrdiff_t)0);
printf("Heap Location:\n");

printf("\t Initial end of  heap:%p\n",b);
brk(b+4);
b=sbrk((ptrdiff_t)0);
printf("\tNew end of heap:%p\n",b);

return 0;
}