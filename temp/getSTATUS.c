#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t child_pid;

    // Create a child process
    child_pid = fork();

    if (child_pid == -1) {
        // Error handling if fork fails
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) {
        // Code for the child process
        printf("Child process\n");
        // Perform some task in the child process
        // ...

        // Terminate the child process with a success status (exit code 0)
        exit(EXIT_SUCCESS);
    } else {
        // Code for the parent process
        printf("Parent process\n");

        // Wait for the child process to complete
        int status;
        waitpid(child_pid, &status, 0);

        if (WIFEXITED(status)) {
            // Child process terminated
            int exit_status = WEXITSTATUS(status);
            if (exit_status == 0) {
                printf("Child process exited successfully\n");
            } else {
                printf("Child process exited with status %d\n", exit_status);
            }
        } else {
            // Child process did not terminate normally
            printf("Child process did not exit normally\n");
        }
    }

    return 0;
}
