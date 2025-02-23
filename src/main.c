#include "../include/quiz.h"
#include "ipc.h"
#include "game.h"
#include "options.h"
#include "ui.h"


int main(int argc, char *argv[]) {
    int questionPipe[2];  // Pipe pour envoyer les questions du fils au père
    int answerPipe[2];    // Pipe pour envoyer les réponses du père au fils
    int shm_id;           // Identifiant pour la mémoire partagée
    int numberOfQuestionsToAsk = 4;  // Définir le nombre de questions pour le quiz (4 par défaut)
    int numberOfAnswerOptions = 2;   // Définir le nombre de réponses possibles à afficher par question (2 par défaut)

    initUI();  // Initialisation de ncurses

    bool hasColors = has_colors(); // Test si le terminal support les couleurs de ncurses
    if (hasColors) {
        start_color(); // Utilisation de couleurs avec ncurses
        init_pair(1, COLOR_YELLOW, COLOR_BLACK); // Définition d'un couple couleur: police jaune, fond noir
        init_pair(2, COLOR_BLUE, COLOR_BLACK);   // Définition d'un couple couleur: police bleu, fond noir
    }

    echo();  // Activation de l'echo pour pouvoir voir l'entrée utilisateur en temps réel

    // Traitement des options de ligne de commande
    parseOptions(argc, argv, &numberOfQuestionsToAsk, &numberOfAnswerOptions);

    srand(time(NULL)); // Pour obtenir un seed aléatoire pour la sélection des questions et options

    // Initialisation des pipes pour la communication
    if (pipe(questionPipe) == -1 || pipe(answerPipe) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    shm_id = initSharedMemory(); // Initialisation de la mémoire partagée pour le score

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {  // Processus fils
        close(questionPipe[0]); // Fermer le côté lecture du pipe de question
        close(answerPipe[1]);  // Fermer le côté écriture du pipe de réponse

        gameLoop(questionPipe[1], answerPipe[0], shm_id, numberOfQuestionsToAsk, numberOfAnswerOptions);

        close(questionPipe[1]); // Fermer le côté écriture après utilisation
        close(answerPipe[0]);  // Fermer le côté lecture après utilisation
        exit(0);
    } else {  // Processus père
        close(questionPipe[1]); // Fermer le côté écriture du pipe de question
        close(answerPipe[0]);  // Fermer le côté lecture du pipe de réponse

        for (int i = 0; i < numberOfQuestionsToAsk; i++) {
            mcq_t question;
            readFromPipe(questionPipe[0], &question, sizeof(mcq_t)); // Récupération de la question depuis le pipe de question, envoyé par le processus fils

            displayQuestion(question, numberOfAnswerOptions, hasColors);  // Affichage de question
            
            char answer;
            do {
                scanw("%c", &answer);
            } while (answer < 'A' || answer > 'A' + numberOfAnswerOptions - 1); // Valider la réponse 

            writeToPipe(answerPipe[1], &answer, sizeof(answer)); // REnvoi de réponse vers le pipe de réponse, envoyé vers le processus fils pour la vérifier
        }

        wait(NULL);  // Attendre la fin du processus fils
        
        close(questionPipe[0]); // Fermer le côté lecture après utilisation
        close(answerPipe[1]);  // Fermer le côté écriture après utilisation
        
        // Calculer le score et exécuter le programme correspondant à la réussite ou à l'échec
        displayResult(shm_id, numberOfQuestionsToAsk);

        removeSharedMemory(shm_id); // Nettoyage de la mémoire partagée
    }
    closeUI();  // Fermer ncurses avant de terminer
    
    return 0;
}