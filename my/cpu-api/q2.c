#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

// 동일한 파일 디스크립터로 부모 프로세스와 자식 프로세스에서 모두 접근 가능하다.
int main(int argc, char *argv[])
{
    char *filepath = "./q2.txt";
    int fdInParent = open(filepath, O_CREAT|O_RDONLY, 0644);
    if (fdInParent < 0) {
        perror("open");
        return 1;
    }

    printf("fd %d\n", fdInParent);

    // char *content = "Hello, World!";
    // if (write(fd, content, strlen(content)) == -1) {
    //     perror("write");
    //     close(fd);
    //     return 1;
    // }

    //
    // char buffer[128];
    // ssize_t bytesRead;
    // bytesRead = read(fd, buffer, sizeof(buffer) - 1);
    // if (bytesRead == -1) {
    //     perror("read");
    //     close(fd);
    //     return 1;
    // }
    //
    // buffer[bytesRead] = '\0';
    // printf("file content: '%s'\n", buffer);


    int p = fork();
    if (p < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }

    if (p == 0) {
        // child
        printf("read in child\n");

        int fdInChild = open(filepath, O_RDONLY, 0644);
        if (fdInChild < 0) {
            perror("open");
            return 1;
        }

        // // 파일 오프셋을 파일의 시작으로 이동
        // if (lseek(fd, 0, SEEK_SET) == (off_t) -1) {
        //     perror("lseek");
        //     close(fd);
        //     return 1;
        // }

        char buffer[128];
        ssize_t bytesRead;
        bytesRead = read(fdInChild, buffer, sizeof(buffer) - 1);
        if (bytesRead == -1) {
            perror("read in child\n");
            close(fdInChild);
            return 1;
        }

        buffer[bytesRead] = '\0';
        printf("file content in child: '%s'\n", buffer);

        // 파일 닫기
        if (close(fdInChild) == -1) {
            perror("close");
            return 1;
        }
    } else {
        // parent
        wait(NULL);
        printf("read in parent\n");

        // 파일 오프셋을 파일의 시작으로 이동
        // if (lseek(fdInParent, 0, SEEK_SET) == (off_t) -1) {
        //     perror("lseek");
        //     close(fdInParent);
        //     return 1;
        // }

        char buffer[128];
        ssize_t bytesRead;
        bytesRead = read(fdInParent, buffer, sizeof(buffer) - 1);
        if (bytesRead == -1) {
            perror("read in parent\n");
            close(fdInParent);
            return 1;
        }

        buffer[bytesRead] = '\0';
        printf("file content in parent: '%s'\n", buffer);

        // 파일 닫기
        if (close(fdInParent) == -1) {
            perror("close");
            return 1;
        }
    }

    return 0;
}
