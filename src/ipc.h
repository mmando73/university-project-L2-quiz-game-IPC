#ifndef IPC_H
#define IPC_H

#include "../include/quiz.h"

#define R 0 //Pour le fichier du mode lecture de la tube de communication "Read"
#define W 1 //Pour le fichier du mode érciture de la tube de communication "Write"

// Créer un tube de communication anonyme
void initPipes(int pipefd[2]); 

// Fermer un tube de communication
void closePipe(int pipefd);

// Ercire dans un tube de communication
void writeToPipe(int pipefd, const void *data, size_t dataSize);

// Lecture depuis un tube de communication
void readFromPipe(int pipefd, void *buffer, size_t bufferSize);

// Fonction pour initialiser la mémoire partagée
int initSharedMemory();

// Fonction pour accéder à la mémoire partagée
int* accessSharedMemory(int shm_id);

// Fonction pour se détacher de la mémoire partagée
void detachSharedMemory(int *shm_ptr);

// Fonction pour supprimer la mémoire partagée
void removeSharedMemory(int shm_id);

#endif