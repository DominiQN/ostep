#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main () {
    int pipefd[2];
    if (pipe(pipefd) < 0) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    char *flag = "done";
    int p = fork();

    if (p < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (p == 0) {
        // child
        if (close(pipefd[0]) < 0) {
            perror("pipe out close in child");
            exit(EXIT_FAILURE);
        }
        printf("hello\n");
        if (write(pipefd[1], flag, strlen(flag)) < 0) {
            perror("write in child");
            exit(EXIT_FAILURE);
        }

        if (close(pipefd[1]) < 0) {
            perror("pipe in close in child");
            exit(EXIT_FAILURE);
        }

    } else {
        // parent
        if (close(pipefd[1]) < 0) {
            perror("pipe close in parent");
            exit(EXIT_FAILURE);
        }

        char buffer[strlen(flag)];
        read(pipefd[0], buffer, strlen(buffer));

        printf("goodbye\n");

        if (close(pipefd[0]) < 0) {
            perror("pipe out close in parent");
            exit(EXIT_FAILURE);
        }
    }

    return EXIT_SUCCESS;
}
