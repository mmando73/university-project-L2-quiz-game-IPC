#include "game.h"
#include "ipc.h"
#include "questions.h"
#include "ui.h"

mcq_t* shuffleOptions(mcq_t *question, int numOptions) {
    if (numOptions > 4 || numOptions < 2) {
        fprintf(stderr, "ERROR_game.c: the options count value has to be between 2 and 4.\n");
        exit(EXIT_FAILURE);
    }

    mcq_t *questionShuffledOptions = malloc(sizeof(mcq_t));
    if (questionShuffledOptions == NULL) {
        fprintf(stderr, "ERROR_game.c: Memory allocation error in shuffleOptions().\n");
        exit(EXIT_FAILURE);
    }

    // On recopie la chaine de caractères de la question
    strcpy(questionShuffledOptions->question, question->question);

    /* On crée un tableau des options en mettant la chaine de caractères du choix valide en premier
     * comme ça on est sûr que peu importe le nombre d'options à afficher
     * on aura toujours le bon choix parmis ceux affichés */
    char *validAnswer = getValidChoiceString(*question);
    char *options[4] = {validAnswer, "", "", ""};
    bool usedIndices[4] = {0,0,0,0}; // Tableau pour suivre les indices utilisés

    // On récupère toutes les options
    char *allOptions[4] = {question->A, question->B, question->C, question->D};

    // On marque l'indice du choix valide dans allOptions comme utilisée pour ne pas avoir 2 fois la même option 
    for (int i = 0; i < 4; i++) {
        if (strcmp(allOptions[i], validAnswer) == 0) {
        usedIndices[i] = true;
        break;
        }
    }

    // Le choix aléatoire du reste des options
    for (int i = 1; i < numOptions; i++) {
        int k;
        do {
            k = rand() % 4;
        } while (usedIndices[k]);  // Vérification que l'option n'est pas déjà utilisée
        options[i] = allOptions[k];
        usedIndices[k] = true;
    }

    // On mélange la liste des options
    for (int i = numOptions - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        char *temp = options[i];
        options[i] = options[j];
        options[j] = temp;
    }

    // On copie les options mélangés dans la structure
    strcpy(questionShuffledOptions->A, options[0]);
    strcpy(questionShuffledOptions->B, options[1]);
    if (numOptions > 2) strcpy(questionShuffledOptions->C, options[2]);
    if (numOptions > 3) strcpy(questionShuffledOptions->D, options[3]);

    // On met à jour le caractère du choix valide
    questionShuffledOptions->validChoice = 'A';
    for (int i = 0; i < numOptions; i++) {
        if (strcmp(options[i], validAnswer) == 0) {
            questionShuffledOptions->validChoice += i;
            break;
        }
    }

    return questionShuffledOptions;
}

void updateScore(int shm_id, bool correct) {
    // Accés à la mémoire partagée et récupération du score
    int *score = accessSharedMemory(shm_id);

    // Mise à jour du score stocké dans la mémoire partagée
    if (correct) *score += 1;  
    
    // Se détacher de la mémoire partagée
    detachSharedMemory(score);
}

void checkWinLoss(int shm_id, int totalQuestions) {
    // Accés à la mémoire partagée et récupération du score
    int *score = accessSharedMemory(shm_id);

    // Calcule du pourcentage de réponses correctes
    float percentage = ((float)*score / totalQuestions) * 100;

    // Se détacher de la mémoire partagée
    detachSharedMemory(score);

    // Vérification de la condition de gain/perte et exécution du programme correspondant
    pid_t pid = fork();
    if (pid == 0) {  // Processus enfant
        if (percentage >= 50.0) {
            execl("./success", "success", NULL);
        } else {
            execl("./failure", "failure", NULL);
        }
        fprintf(stderr, "ERROR_game.c: Exec failed in checkWinLoss()\n"); // execl ne retourne que s'il y a une erreur
        exit(EXIT_FAILURE);
    } else if (pid > 0) {  // Processus parent
        int status;
        waitpid(pid, &status, 0);  // Attendre que le processus enfant se termine
    } else {
        fprintf(stderr, "ERROR_game.c: Fork failed in checkWinLoss()\n");
    }
}



void gameLoop(int questionPipeW, int answerPipeR, int shm_id, int numberOfQuestionsToAsk, int numberOfOptions) {
    mcq_t *allQuestions = loadQuestions();  // Chargement de toutes les questions depuis questions.txt

    // Sélectionne aléatoirement un sous-ensemble de questions pour le jeu
    mcq_t *selectedQuestions = selectRandomQuestions(allQuestions, ALL_QUESTIONS, numberOfQuestionsToAsk);

    for (int i = 0; i < numberOfQuestionsToAsk; i++) {
        mcq_t *question = shuffleOptions(&selectedQuestions[i], numberOfOptions);
    
        // Envoyer la question sélectionnée au processus père
        writeToPipe(questionPipeW, question, sizeof(mcq_t)); // Envoyer la question au processus père

        // Attendre et lire la réponse du processus père
        char answer;
        readFromPipe(answerPipeR, &answer, sizeof(answer)); // Recevoir la réponse du processus père

        // Vérifier si la réponse est correcte et mettre à jour le score
        if (answerCheck(*question, answer)){
            updateScore(shm_id, true); // Incrémenter le score en mémoire partagée si la réponse est correcte
        } 

        // Libération de la mémoire
        free(question);
    }

    // Libération de la mémoire
    free(allQuestions);
    free(selectedQuestions);
    
}
