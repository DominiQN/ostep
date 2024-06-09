#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

// 동일한 파일 디스크립터로 부모 프로세스와 자식 프로세스에서 모두 접근 가능하다.
int main(int argc, char *argv[])
{
    char *filepath = "./q2-2.txt";
    int fd = open(filepath, O_CREAT|O_RDWR|O_TRUNC, 0755);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    printf("fd %d\n", fd);

    int p = fork();
    if (p < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }

    if (p == 0) {
        // child

        // int fdInChild = open(filepath, O_CREAT|O_RDWR, 0755);
        // if (fdInChild < 0) {
        //     perror("open");
        //     return 1;
        // }

        // // 파일 오프셋을 파일의 시작으로 이동
        // if (lseek(fd, 0, SEEK_SET) == (off_t) -1) {
        //     perror("lseek");
        //     close(fd);
        //     return 1;
        // }

        char writeBuffer[100];
        char *data = "write in child";

        for (int i = 0; i < 1000; i++) {
            sprintf(writeBuffer, "%s %d\n", data, i);
            if (write(fd, writeBuffer, strlen(writeBuffer)) < 0) {
                perror("write in child");
                close(fd);
                exit(EXIT_FAILURE);
            }
        }
    } else {
        // parent
        // wait(NULL);

        // 파일 오프셋을 파일의 시작으로 이동
        // if (lseek(fdInParent, 0, SEEK_SET) == (off_t) -1) {
        //     perror("lseek");
        //     close(fdInParent);
        //     return 1;
        // }

        char writeBuffer[100];
        char *data = "write in parent";

        for (int i = 0; i < 1000; i++) {
            sprintf(writeBuffer, "%s %d\n", data, i);
            if (write(fd, writeBuffer, strlen(writeBuffer)) < 0) {
                perror("write in parent");
                close(fd);
                exit(EXIT_FAILURE);
            }
        }

    }

    close(fd);
    return EXIT_SUCCESS;
}
