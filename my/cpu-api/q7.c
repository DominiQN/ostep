#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/fcntl.h>

int main() {
    int p = fork();

    if (p < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (p == 0) {
        // child
        char *resultfile = "./q7-result.txt";
        int resultfd = open(resultfile, O_CREAT|O_WRONLY|O_TRUNC, 0755);
        char buffer[100];

        int p1result = printf("Hello worlds!");
        sprintf(buffer, "p1 result: %d\n", p1result);

        // printf의 결과는 string의 길이였다.
        if (write(resultfd, buffer, strlen(buffer)) < 0) {
            perror("write p1 result");
            exit(EXIT_FAILURE);
        }

        if (close(STDOUT_FILENO) < 0) {
            perror("close in child");
            exit(EXIT_FAILURE);
        }

        // stdout 출력 안 됨
        int p2result = printf("Hello in child.\n");

        // stdout이 닫혀 있을 때, printf의 결과는 -1이다.
        sprintf(buffer, "p2 result: %d\n", p2result);
        if (write(resultfd, buffer, strlen(buffer)) < 0) {
            perror("write p2 result");
            exit(EXIT_FAILURE);
        }
    } else {
        // parent
        int status;

        wait(&status);

        // 결과는 0
        printf("child process result: %d\n", status);
    }

    return EXIT_SUCCESS;
}
