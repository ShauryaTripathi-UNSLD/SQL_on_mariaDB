#include <unistd.h>
#include <stdio.h>
#include <sys/types.h> // Include the sys/types.h header file

int main() {
    
    pid_t process_id = getpid();
    printf("Process ID: %d\n", process_id);
    return 0;
}
