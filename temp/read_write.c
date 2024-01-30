#include <unistd.h>
#include <stdio.h>
#include <string.h>
int main() {
    char buffer[100];
    printf("Enter a message: ");
    ssize_t bytesRead = read(STDIN_FILENO, buffer, sizeof(buffer));
    printf("Read %zd bytes: %s\n", bytesRead, buffer);

    // Writing to STDOUT_FILENO
    write(STDOUT_FILENO, buffer, strlen(buffer));

    return 0;
}
