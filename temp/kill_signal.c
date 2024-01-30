#include <signal.h>
#include <stdio.h>
#include <sys/types.h>


void signal_handler(int signo)
{
    printf("Received signal %d\n", signo);
}

char* numberToString(int number) {
    int length = snprintf(NULL, 0, "%d", number); // Get the length of the string representation
    char* str = malloc(length + 1); // Allocate memory for the string (+1 for null terminator)
    snprintf(str, length + 1, "%d", number); // Convert the number to string
    return str;
}

int main()
{
    
    int child = fork();
    if (child == 0)
    {
        printf("Waiting for a signal...\n");
        printf("%d\n", getpid());
        signal(SIGINT, signal_handler); // Set a custom handler for SIGINT
        pause();                        // Wait for a signal to interrupt the program
        puts("child 1 ended");
        exit(1);
    }

    int child2=fork();
    if (child2 == 0 ){
        int n;
        scanf("%d",&n);
        puts("child 2 is going to end child 1");
        int child3=fork();
        if(child3==0){
        execl("/bin/kill","kill","-SIGINT",numberToString(child),NULL);
        exit(0);
        }
        wait(NULL);
        for(int i=0;i<10;i++)printf("%d",i);
        exit(0);
    }
    wait(NULL);
    wait(NULL);

    // To send a signal to the process, you can use the kill command in another terminal:
    // kill -SIGINT <process_id>

    return 0;
}
