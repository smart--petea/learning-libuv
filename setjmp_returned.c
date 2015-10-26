/*Write a program to see what happens if we try to longjmp() into a function that has already returned*/
#include <stdio.h>
#include <setjmp.h>

static jmp_buf env;

static void setMyJmp()
{
    if(setjmp(env) == 0)
        printf("setMyJmp init \n");
    else
        printf("setMyJmp from longjmp");
}

int main()
{
    setMyJmp();

    printf("before longjmp\n");
    longjmp(env, 1);
    printf("after longjmp\n");

    return 0;
}
