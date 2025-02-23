#ifndef QUIZ_H
#define QUIZ_H

#define _POSIX_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <time.h>
#include <ctype.h>
#include <errno.h>
#include <getopt.h>
#include <ncurses.h>
#include <locale.h>
#include <signal.h>



typedef struct mcq {
    char question[256]; // La question posée
    char A[256];        // Option de réponse A
    char B[256];        // Option de réponse B
    char C[256];        // Option de réponse C
    char D[256];        // Option de réponse D
    char validChoice;   // Lettre de la réponse valide ('A', 'B', 'C', ou 'D')
} mcq_t;

#endif