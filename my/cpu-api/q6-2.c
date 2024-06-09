#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    // 첫 번째 자식 프로세스를 생성하고 프로세스 그룹 리더로 설정
    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // 자식 프로세스
        printf("Child 1 PID: %d, PGID: %d\n", getpid(), getpgid(0));

        // 새로운 프로세스 그룹을 생성하고 그룹 리더로 설정
        setpgid(0, 0);
        printf("Child 1 new PGID: %d\n", getpgid(0));

        // 무한 루프
        while (1) {
            sleep(1);
        }
    } else {
        // 부모 프로세스
        printf("Parent PID: %d, PGID: %d\n", getpid(), getpgid(0));

        // 두 번째 자식 프로세스를 생성
        pid_t pid2 = fork();
        if (pid2 < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid2 == 0) {
            // 자식 프로세스
            printf("Child 2 PID: %d, PGID: %d\n", getpid(), getpgid(0));

            // 첫 번째 자식 프로세스의 그룹에 포함
            setpgid(0, pid);
            printf("Child 2 new PGID: %d\n", getpgid(0));

            // 무한 루프
            while (1) {
                sleep(1);
            }
        } else {
            // 부모 프로세스

            // 첫 번째 자식 프로세스가 프로세스 그룹 리더로 설정된 것을 확인하기 위해 잠시 대기
            sleep(1);

            // 첫 번째 자식 프로세스 그룹에 시그널 전송 (SIGTERM)
            printf("Sending SIGTERM to process group %d\n", pid);
            killpg(pid, SIGTERM);

            // 두 번째 자식 프로세스가 종료되었는지 확인
            waitpid(pid2, NULL, 0);
        }
    }

    return EXIT_SUCCESS;
}
