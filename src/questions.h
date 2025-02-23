#ifndef QUESTIONS_H
#define QUESTIONS_H

#include "../include/quiz.h"

#define ANSWER_POSITION 8 // Position du caractère de réponse valide dans "questions.txt" (ex: "Answer: A")
#define ALL_QUESTIONS 45  // Nombre total des questions dans "questions.txt"

// Vérifie si la chaîne 'a' commence par la chaîne 'b'
bool startsWith(const char *a, const char *b); 

// Enlève le préfixe "Q: " d'une ligne de question
const char* stripQuestionPrefix(const char *a); 

// Enlève le préfixe "A - ", "B - ", etc., d'une ligne de choix de réponse
const char* stripAnswerPrefix(const char *a); 

// Extrait le caractère de réponse valide (ex: 'A' de "Answer: A")
char extractValidChoice(const char *a); 

// Renvoie la chaîne de caractères correspondant au choix valide dans une question
char* getValidChoiceString(mcq_t q); 

// Vérifie si un caractère donné correspond à celui de la réponse valide
bool answerCheck(mcq_t question, char answer);

// Charge les questions depuis le fichier "questions.txt" et renvoie un tableau de mcq_t
mcq_t* loadQuestions(); 

// Sélectionne un sous-ensemble de questions aléatoires depuis un tableau de toutes les questions
mcq_t* selectRandomQuestions(mcq_t *allQuestions, int allQuestionCount, int selectCount); 

#endif