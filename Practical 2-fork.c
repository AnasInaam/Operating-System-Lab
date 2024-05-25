#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int n, i;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        if (fork() == 0) {
            printf("Child with PID %d created by parent with PID %d\n", getpid(), getppid());
            return 0;
        }
    }

    for (i = 0; i < n; i++) {
        wait(NULL);
    }

    return 0;
}

/*
### Explanation
1. *Libraries*: Include standard I/O and system calls libraries.
2. *Input*: Read the number of processes to create.
3. *Fork Loop*: Create n child processes using fork(), each printing its PID and parent PID, then exit.
4. *Wait Loop*: Parent process waits for all child processes to finish using wait(NULL).  */
