#include <sys/shm.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int main() {

    int shmid;
    char *shm;
    key_t key;

    key = 1234;

    if(fork() == 0){
        shmid = shmget(key, sizeof(shm), 0666 | IPC_CREAT);
        shm = shmat(shmid, 0, 0);
        char *s = shm;
        *s = '\0';
        strcat(s, "Hello from the child");

        printf("Child process just wrote - %s - ;\n", shm);
        shmdt(shm);
    }
    else{
        shmid = shmget(key, sizeof(shm), 0666 | IPC_CREAT);
        shm = shmat(shmid, 0, 0);
        wait(NULL);
        printf("Parent process just red - %s - ;\n", shm);
        shmdt(shm);
    }

    return 0;
}