#ifndef UI_H
#define UI_H

#include "../include/quiz.h"

// Initialisation de l'interface utilisateur
void initUI();

// Nettoyage et sortie de l'interface utilisateur
void closeUI();

// Affichage d'une question avec ncurses
void displayQuestion(mcq_t question, int numberOfOptions, bool hasColors);

// Fonction pour exécuter les programme en charge de l'affichag des messages de fin, succès ou échec, en plus du score
void displayResult(int shm_id, int totalQuestions);

#endif