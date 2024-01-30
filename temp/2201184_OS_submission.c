#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>


int main()
{
    int channel1[2], channel2[2];
    if (pipe(channel1) < 0 || pipe(channel2) < 0)
    {
        perror("we were unable to create one of the/both pipes successfully, exiting with SIGPIPE error");
        exit(SIGPIPE);
    }
    pid_t child1;
    // child1 starts here..................................................
    if (child1 = fork() == 0)
    {
        char buff;
        // closing all pipes which arent required
        close(channel1[0]);
        close(channel2[1]);
        close(channel2[0]);
        puts("<--- give inputs, to simulate EOF via terminal, press \"Ctrl+D\"--->");
        while (1)
        {
            buff = getchar();
            write(channel1[1], &buff, 1);
        }
        exit(0); // not necessory as while loop will never end unless interrupted
    }
    pid_t child2;
    // child2 starts here...................................................
    if (child2 = fork() == 0)
    {
        // closing all pipes which arent required
        close(channel1[1]);
        close(channel2[0]);
        char buff;
        while (1)
        {
            read(channel1[0], &buff, 1);
            buff++;
            write(channel2[1], &buff, 1);
        }
        exit(0); // not necessory.....
    }

    // closing unneccessory pipe ends

    close(channel1[0]);
    close(channel1[1]);
    close(channel2[1]);

    char buff;
    while (1)
    {
        if (read(channel2[0], &buff, 1) > 0)
        {
            buff--;
            if (buff != EOF)
                putchar(buff);
            else
            {
                kill(child1, 0);
                kill(child2, 0);
                puts("child processes are terminated successfully, terminating main.......exiting successfully......");
                exit(0);
            }
        }
        else {
                kill(child1, SIGPIPE);
                kill(child2, SIGPIPE);
                puts("child processes are terminated on pipe error/other error, terminating main.......exiting abruptly......");
                exit(SIGPIPE);
        }
    }

    return 0;
}