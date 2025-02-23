#include "ui.h"
#include "ipc.h"


void initUI() {
    initscr();  // Initialiser l'écran avec ncurses
    echo();     // Afficher les caractères saisis à l'écran
}


void closeUI() {
    endwin();  // Terminer le mode ncurses
}


void displayQuestion(mcq_t question, int numberOfOptions, bool hasColors) {
    clear(); // Effacer l'écran
    if (hasColors){
        attron(COLOR_PAIR(2));  // Affichage du texte de question en bleu
        printw("%s\n", question.question);  
        attroff(COLOR_PAIR(2));  

        // Afficher les options de réponse
        attron(COLOR_PAIR(1));  // Texte en jaune pour les options
        printw("A) %s\n", question.A);
        if (numberOfOptions > 1) printw("B) %s\n", question.B);
        if (numberOfOptions > 2) printw("C) %s\n", question.C);
        if (numberOfOptions > 3) printw("D) %s\n", question.D);
        attroff(COLOR_PAIR(1)); 
    } else {
        //Affichage de question
        printw("%s\n", question.question);  

        // Afficher les options de réponse
        printw("A) %s\n", question.A);
        if (numberOfOptions > 1) printw("B) %s\n", question.B);
        if (numberOfOptions > 2) printw("C) %s\n", question.C);
        if (numberOfOptions > 3) printw("D) %s\n", question.D);
    }
    
    attron(A_BOLD); // Texte en gras pour l'instruction
    printw("\n\n\nEnter your answer: ");
    attroff(A_BOLD);
    refresh();  // Rafraîchir l'affichage à l'écran
}



void displayResult(int shm_id, int totalQuestions) {
    clear();  // Effacer l'écran

    // Accés à la mémoire partagée et récupération du score
    int *score = accessSharedMemory(shm_id);

    // Calcule du pourcentage de réponses correctes
    float percentage = ((float)*score / totalQuestions) * 100;

    // Se détacher de la mémoire partagée
    detachSharedMemory(score);

    char percentageStr[20];
    sprintf(percentageStr, "%f", percentage);
    // Terminez la session ncurses avant de lancer un autre programme
    closeUI();


    pid_t pid = fork(); // Création d'un processus fils pour exécuter un programme d'affichage et revenir dans la fonction à la fin
        if (pid == 0) { 
            if (percentage >= 50.0) {
                execl("./success", "success", percentageStr, NULL); 
            } else {
                execl("./failure", "failure", percentageStr, NULL);
            }
            fprintf(stderr, "Exec failed\n");
            exit(EXIT_FAILURE);
        } else if (pid > 0) {
            int status;
            waitpid(pid, &status, 0);
        } else {
            fprintf(stderr, "Fork failed\n");
        }
}