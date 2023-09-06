#include "apue.h"

int main(void)
{
    int c;
    int count = 0;

    while( (c = getc(stdin)) != EOF )
    {
        count++;
        if(putc(c,stdout) == EOF)
            err_sys("output error");
    }

    if(ferror(stdin))
        err_sys("input error");
    printf("%d\n", count);

    exit(0);
}

