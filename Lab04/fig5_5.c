#include "apue.h"

int main(void)
{
    char buf[MAXLINE];
    int count = 0;

    setvbuf(stdout,buf,_IONBF,MAXLINE);

    while( (fgets(buf,MAXLINE,stdin)) != NULL )
    {
        count++;
        if(fputs(buf,stdout) == EOF)
            err_sys("output error");
    }

    if(ferror(stdin))
        err_sys("input error");
    printf("%d\n", count);

    exit(0);
}

