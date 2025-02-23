#include "../include/quiz.h"

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, ""); // Configurer la localisation pour supporter UTF-8
    initscr();  // Initialisation de ncurses
    clear();   // Efface l'écran

    if(has_colors()){
        start_color();
        init_pair(1, COLOR_GREEN, COLOR_BLACK);  // Définition d'un couple couleur: police vert, fond noir 

        attron(COLOR_PAIR(1));

        printw( "\n\n\t██    ██  ██████  ██    ██     ██     ██  ██████  ███    ██   ██ \n" 
                    "\t ██  ██  ██    ██ ██    ██     ██     ██ ██    ██ ████   ██   ██ \n" 
                    "\t  ████   ██    ██ ██    ██     ██  █  ██ ██    ██ ██ ██  ██   ██ \n"
                    "\t   ██    ██    ██ ██    ██     ██ ███ ██ ██    ██ ██  ██ ██      \n"   
                    "\t   ██     ██████   ██████       ███ ███   ██████  ██   ████   ██ \n\n\n");

        double score = atof(argv[1]);
        printw("\tYour score is: %.f%%", score); // Affichage du score
        attroff(COLOR_PAIR(1));
    } else {
        printw( "\n\n\t██    ██  ██████  ██    ██     ██     ██  ██████  ███    ██   ██ \n" 
                    "\t ██  ██  ██    ██ ██    ██     ██     ██ ██    ██ ████   ██   ██ \n" 
                    "\t  ████   ██    ██ ██    ██     ██  █  ██ ██    ██ ██ ██  ██   ██ \n"
                    "\t   ██    ██    ██ ██    ██     ██ ███ ██ ██    ██ ██  ██ ██      \n"   
                    "\t   ██     ██████   ██████       ███ ███   ██████  ██   ████   ██ \n\n\n");

        double score = atof(argv[1]);
        printw("\tYour score is: %.f%%", score); // Affichage du score
    }
    

    attron(A_ITALIC); // Texte en italique pour l'instruction
    printw("\n\n\n\n\nEnd of the game. Press any key to exit.");
    refresh(); // Rafraîchir l'affichage à l'écran
    attroff(A_ITALIC);

    getch();    // Attendre pour une entrée utilisateur

    endwin();  // Terminer le mode ncurses avant de quitter

    return 0;
}