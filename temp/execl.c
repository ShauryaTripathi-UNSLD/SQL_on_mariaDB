#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        execl("/bin/ls", "ls", "-l", NULL);
        perror("execl"); // This line will be reached only if execl fails
        return 1;
    } else if (pid > 0) {
        // Parent process
        wait(NULL); // Wait for the child process to finish
        printf("Child process completed.\n");
    } else {
        // Fork failed
        perror("fork");
        return 1;
    }

    return 0;
}
