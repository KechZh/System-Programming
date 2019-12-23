#include <stdio.h>
#include "apue.h"

void accumulation(int d_sum);

int main()
{
    FILE* sum;
    int total_sum=0;
    pid_t pid[5];
    int year=5, week=52, day=7;

    sum = fopen("sum.txt", "w");
    fprintf(sum, "%d\n", 0);
    fclose(sum);

    /**********************************************************/

    TELL_WAIT();
    FILE *fp;
    int i,j,k,l;
    for(i=0; i<year; i++)
    {
        if((pid[i]=fork())<0)
            err_sys("fork error");
        else if(pid[i]==0)
        {
            WAIT_PARENT();
            for(j=1; j<=week; j++)
            {
                char filename[20];
                sprintf(filename,"%d-%02d.txt",i+1,j);
                fp=fopen(filename,"r");
                for(k=0; k<day; k++)
                {
                    int part_sum=0;
                    for(l=0; l<96; l++)
                    {
                        int value;
                        fscanf(fp,"%d",&value);
                        part_sum+=value;
                    }
                    accumulation(part_sum);
                }
                fclose(fp);
            }
            TELL_PARENT(getppid());
            exit(0);
        }
        else
        {
            TELL_CHILD(pid[i]);
            WAIT_CHILD();
        }
    }

    /**********************************************************/

    sum = fopen("sum.txt", "r");
    fscanf(sum, "%d", &total_sum);
    printf("Day_Average = %d\n",total_sum/(year*week*day));
    fclose(sum);

    return 0;
}

void accumulation(int d_sum)    //Accumulating the daily sum to "sum.txt".
{
    FILE* sum;
    int tmp=0;

    sum = fopen("sum.txt", "r+");
    fscanf(sum, "%d", &tmp);

    tmp += d_sum;

    rewind(sum);
    fprintf(sum, "%d", tmp);
    fclose(sum);

    return;
}
