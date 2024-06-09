#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int p1 = fork();

    if (p1 < 0) {
        perror("fork p1");
        exit(EXIT_FAILURE);
    }

    if (p1 == 0) {
        // child
        printf("sleep 1s p1\n");
        sleep(3);
        printf("sleep 1s p1 done\n");
    } else {
        // parent
        printf("fork p1 result: %d\n", p1);


        int p2 = fork();
        if (p2 < 0) {
            perror("fork p2");
            exit(EXIT_FAILURE);
        }

        if (p2 == 0) {
            // 자식이 없는 프로세스에서 wait를 호출할 경우 -1이 반환됨
            pid_t p2waitresult = wait(NULL);
            printf("p2 wait result %d\n", p2waitresult);

            printf("sleep 1s p2\n");
            sleep(5);
            printf("sleep 1s p2 done\n");

            return EXIT_SUCCESS;
        }
        printf("fork p2 result: %d\n", p2);

        // 자식 프로세스가 여러 개일 경우,
        // 먼저 종료되는 자식 프로세스의 pid를 반환
        pid_t waitresult = waitpid(p2, NULL);
        printf("wait result: %d\n", waitresult);
    }

    return EXIT_SUCCESS;
}
