#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <setjmp.h>

jmp_buf checkpoint;

void alarm_handler(int signo)
{
    printf("Parent invoked SIGALRM\n");
    longjmp(checkpoint, 69);
}

char *numberToString(int number)
{
    int length = snprintf(NULL, 0, "%d", number); // no loop needed for couting THE FKIN DIGITS
    char *str = malloc(length + 1);
    snprintf(str, length + 1, "%d", number);
    return str;
}

int main(int argc, char *argv[])
{
    ////////////////////////////////////////////////////////////
    int NO_INPUT_FILE = 1, NO_OUTPUT_FILE = 1, fd1, fd2, arg_n = 0;
    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] != '-')
        {
            if (NO_INPUT_FILE == 1)
            {
                fd1 = open(argv[i], O_RDONLY);
                if (fd1 == -1)
                {
                    fprintf(stderr, "Error: Failed to open file %s\n", argv[i]);
                    exit(1);
                }
                NO_INPUT_FILE = 0;
            }
            else if (NO_OUTPUT_FILE == 1)
            {
                fd2 = creat(argv[i], 0644);
                if (fd2 == -1)
                {
                    fprintf(stderr, "Error: Failed to create file %s\n", argv[i]);
                    exit(1);
                }
                NO_OUTPUT_FILE = 0;
            }
            else
            {
                break;
            }
        }
        else
        {
            if (argv[i][0] == "-" && arg_n == 0)
                arg_n = i;
            continue;
        }
    }
    ///////////////////////////////////////////////////////////

    if (!NO_INPUT_FILE)
        if (dup2(fd1, STDIN_FILENO) == -1)
        {
            fprintf(stderr, "Errorxx: Failed to duplicate file descriptor for stdin\n");
            exit(1);
        }
    if (!NO_OUTPUT_FILE)
        if (dup2(fd2, STDOUT_FILENO) == -1)
        {
            fprintf(stderr, "Errorx: Failed to duplicate file descriptor for stdout\n");
            exit(1);
        }

    ///////////////////////////////////////////////////////////

    int pipefd[2];
    if (pipe(pipefd) == -1)
    {
        fprintf(stderr, "Error: Failed to create pipe\n");
        exit(1);
    }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    pid_t child1 = fork();
    if (child1 == -1)
    {
        fprintf(stderr, "Error: Failed to fork first child\n");
        exit(1);
    }
    else if (child1 == 0)
    {

        close(pipefd[1]);

        if (dup2(pipefd[0], STDIN_FILENO) == -1)
        {
// stop the trash, if i am using unnecessory variables,its for possibility for use in future/study purpose, this aint some nuclear launch software

            fprintf(stderr, "Error: Failed to duplicate file descriptor for stdin\n");
            exit(1);
        }
        if (arg_n)
            execl("./count", "count", argv[arg_n], NULL);
        else
            execl("./count", "count", NULL);

        fprintf(stderr, "Error: Failed to execute count program\n");

        close(pipefd[0]);
        exit(0);
    }
    /////////////////////////////////////////////////////////////////
    pid_t child2 = fork();
    if (child2 == -1)
    {
        fprintf(stderr, "Error: Failed to fork second child\n");
        exit(1);
    }
    else if (child2 == 0)
    {

        close(pipefd[0]);

        if (dup2(pipefd[1], STDOUT_FILENO) == -1)
        {
            fprintf(stderr, "Error: Failed to duplicate file descriptor for stdout\n");
            exit(1);
        }

        execl("./convert", "convert", NULL);

        fprintf(stderr, "Error: Failed to execute convert program\n");

        close(pipefd[1]);
        exit(0);
    }
    ///////////////////////////////////////////////////////////////////////////

    // Close the read and write ends of the pipe
    close(pipefd[0]);
    close(pipefd[1]);
    //////////////////////////////////////////////////////////////////////////////////////
    signal(SIGALRM, alarm_handler);
    int result = setjmp(checkpoint); // checkpoint
    if (result == 0)
    {
        //
    }
    else
    {
        // act here
        kill(child1, SIGTERM);
        kill(child2, SIGTERM);
        fprintf(stderr, "childs killed, both/one of the  processes taking too much time to reach the ultimate goal");
        waitpid(-1, NULL, 0);
        waitpid(-1, NULL, 0);
        exit(1);
    }
    alarm(15);
    pid_t pid;
    int status;
    while ((pid=wait(&status)) > 0)
    { /* wait loop */
        fprintf(stderr,"Child %s ended with status code %d\n",(pid==child1?"1":"2"),status);
        //closing other program with same status
        if(pid==child1)kill(child2,status);
        else kill(child1,status);
    }
    //////////////////////////////////////////////////////////////////////////////////
    // Wait for both children to finish
    wait(NULL);
    wait(NULL);

    // Close the file descriptors
    close(fd1);
    close(fd2);

    exit(0);
}
