#include "apue.h"
#include <sys/wait.h>

static void	sig_int(int);		/* our signal-catching function */
int	main(void)
{
    char	buf[MAXLINE];	/* from apue.h */
    pid_t	pid;
    int	status;

    if (signal(SIGINT, sig_int) == SIG_ERR)
        err_sys("signal error");

    printf("## ");
    while (fgets(buf, MAXLINE, stdin) != NULL)
    {
        if (buf[strlen(buf) - 1] == '\n')
            buf[strlen(buf) - 1] = 0; /* replace newline with null */

        char *argv[1024];
        int i=0;
        char *token;
        token=strtok(buf," ");
        while(token!=NULL)
        {
            argv[i++]=token;
            token=strtok(NULL," ");
        }
        argv[i]=NULL;

        if(strcmp(argv[0],"cd")==0)
        {
            chdir(argv[1]);
            printf("## ");
            continue;
        }

        else if ((pid = fork()) < 0)
        {
            err_sys("fork error");
        }

        else if (pid == 0)  		/* child */
        {
            execvp(argv[0], argv);
            err_ret("couldn't execute: %s", buf);
            exit(127);
        }
        /* parent */
        if ((pid = waitpid(pid, &status, 0)) < 0)
            err_sys("waitpid error");
        printf("## ");
    }
    exit(0);
}

void	sig_int(int signo)
{
    printf("interrupt\n## ");
}

