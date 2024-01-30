#include <unistd.h>
#include <signal.h>
#include <stdio.h>

void alarm_handler(int signo) {
    printf("Alarm triggered!\n");
}

int main() {
    signal(SIGALRM, alarm_handler);
    alarm(5); // Set alarm to trigger after 5 seconds
    pause();  // Wait for the alarm signal
    return 0;
}
