#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    int p = fork();

    if (p < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (p == 0) {
        // child
        char *argv[2];
        argv[0] = strdup("/bin/ls");
        argv[1] = NULL;
        execvp(argv[0], argv);
    } else {
        // parent
        wait(NULL);
    }

    return EXIT_SUCCESS;
}
