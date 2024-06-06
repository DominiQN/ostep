#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int x = 100;
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        printf("child x = %d\n", x);
        x = 200;
        printf("changed x = %d\n", x);
    } else {
        printf("parent x = %d\n", x);
        int rc_wait = wait(NULL);
        printf("after wait parent x = %d\n", x);
    }
    return 0;
}
