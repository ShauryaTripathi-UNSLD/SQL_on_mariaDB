#include <setjmp.h>
#include <stdio.h>

jmp_buf jump_buffer;

int main() {
    int result = setjmp(jump_buffer);
    if (result == 0) {
        // This is the initial call
        printf("Initial call\n");
        longjmp(jump_buffer, 10);
        printf("hekllo\n");
    } else {
        printf("%d\n",result);
        // This is the jump back
        printf("Jumped back\n");
    }
    return 0;
}