#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h> // Include the sys/types.h header for pid_t

int main()
{
    // PID of the process you want to kill

    pid_t target_pid = 2347892589346;

    // Sending the SIGTERM signal to terminate the process
    if (kill(target_pid, SIGTERM) == 0)
    {
        printf("Process with PID %d terminated successfully.\n", target_pid);
    }
    else
    {
        perror("kill");
        fprintf(stderr, "Failed to terminate process with PID %d\n", target_pid);
        // Handle the error as needed
    }

    return 0;
}
