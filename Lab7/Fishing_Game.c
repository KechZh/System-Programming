#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
int fish=0;
int status;
void sig_alarm()
{
    if(status==2)
    {
        printf("A fish is biting, pull the fishing rod\n");
        status=3;
        alarm(3);
    }
    else if(status==3)
    {
        printf("The fish was escaped!!\n");
        status=4;
    }
}
void sig_int(int sig)
{
    printf("\n");
    if(status==1)
    {
        printf("Put the fishing rod\nBait into water, waiting fish...\n");
        alarm(rand()%3+3);
        status=2;
    }
    else if(status==2)
    {
        printf("Pull the fishing rod\n");
        status=5;
    }
    else if(status==3)
    {
        alarm(0);
        printf("Pull the fishing rod\n");
        printf("Catch a Fish!!\n");
        fish++;
        printf("Totally caught fishes: %d\n",fish);
        status=5;
    }
    else if(status==4)
    {
        printf("Pull the fishing rod\n");
        printf("The bait was eaten!!\n");
        status=5;
    }
}
void sig_stop()
{
    printf("\n");
    printf("Totally caught fishes: %d\n",fish);
    exit(0);
}
int main(int argc,char *argv[])
{
    srand(time(NULL));
    signal(SIGINT,sig_int);
    signal(SIGTSTP,sig_stop);
    signal(SIGALRM,sig_alarm);
    while (1)
    {
        printf("Fishing rod is ready!\n");
        status=1;
        while (status!=5)
            sleep(1);
    }
    return 0;
}
