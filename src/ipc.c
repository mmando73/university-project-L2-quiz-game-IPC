#include "ipc.h"

void initPipes(int pipefd[2]) {
    // Vérification que le tube a été bien créé
    if (pipe(pipefd) < 0) {
        fprintf(stderr, "ERROR_ipc.c: pipe error in initPipes(): %s.\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
}

void closePipe(int pipefd) {
    close(pipefd);
}

void writeToPipe(int pipefd, const void *data, size_t dataSize) {
    write(pipefd, data, dataSize);
}

void readFromPipe(int pipefd, void *buffer, size_t bufferSize) {
    read(pipefd, buffer, bufferSize);
}

int initSharedMemory() {
    char cwd[256]; //Current working directory
    key_t mem_key = ftok(getcwd(cwd, sizeof(cwd)), 'a');
    int shm_id = shmget(mem_key, sizeof(int), IPC_CREAT | IPC_EXCL | 0666);
    if (shm_id < 0) {
        fprintf(stderr, "ERROR_ipc.c: shmget error in initSharedMemory(): %s.\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    return shm_id;
}

int* accessSharedMemory(int shm_id) {
    int *shm_ptr = (int *)shmat(shm_id, NULL, 0);
    if (shm_ptr == (int *) -1) {
        fprintf(stderr, "ERROR_ipc.c: shmat error in accessSharedMemory(): %s.\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    return shm_ptr;
}

void detachSharedMemory(int *shm_ptr) {
    shmdt(shm_ptr);
}

void removeSharedMemory(int shm_id) {
    shmctl(shm_id, IPC_RMID, NULL);
}