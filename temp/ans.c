#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>

pid_t child1, child2;
void alarm_trigger(int sig)
{
    kill(child1, sig);
    kill(child2, sig);
    puts("terminate");
    exit(0);
}

int main()
{
    int channel1[2], channel2[2];
    if (pipe(channel1) == -1 || pipe(channel2) == -1)
    {
        perror("pipe error");
        exit(1);
    }
    if (child1 = fork() == 0)
    {
        char tempbufffer;
        close(channel1[0]);
        close(channel2[1]);
        close(channel2[0]);
        while (1)
        {
            tempbufffer = getchar();
            write(channel1[1], &tempbufffer, 1);
        }
    }
    if (child2 = fork() == 0)
    {
        close(channel1[1]);
        close(channel2[0]);
        char tempbufffer;
        while (1)
        {
            read(channel1[0], &tempbufffer, 1);
            tempbufffer++;
            write(channel2[1], &tempbufffer, 1);
        }
    }
    close(channel1[0]);
    close(channel1[1]);
    close(channel2[1]);
    // setting up signal
    signal(SIGPIPE, alarm_trigger);
    char tempbufffer;
    while (1)
    {
        if (read(channel2[0], &tempbufffer, 1) > 0)
        {
            tempbufffer--;
            if (tempbufffer != EOF)
                putchar(tempbufffer);
            else
            {
                raise(SIGPIPE);
            }
        }
    }

    return 0;
}