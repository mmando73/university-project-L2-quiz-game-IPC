#include "options.h"

void functionHelp() {
    printf(
        "Usage: ./quiz [OPTIONS]...\nQuiz game via IPC.\n\nOptions:\n"
        "\t-h, --help\n\t\tdisplay this help and exit\n"
        "\t-r, --rules\n\t\tdisplay the rules of the game\n"
        "\t-s, --student\n\t\tdisplay the name of the students who implemented the game\n"
        "\t-a, --answers\n\t\tset the number of possible answers (by default 2, max 4)\n"
        "\t-q, --questions\n\t\tset the number of questions in the quiz (by default 4, max 10)\n");
}

void functionRules() {
    printf(
        "Bienvenue dans ce Quiz game!!! \n\nUne série de questions vous sera posée.\n"
        "Pour chacune des questions, vous aurez plusieurs possibilités de réponse mais "
        "une seule des réponses sera correcte. \nVotre objectif est d'obtenir au moins "
        "50%% de bonnes réponses. \n\nBonne chance !\n");
}

void functionStudent() {
    printf(
        "Ce programme vous est présenté par\nMANDO Mohamad\n"
        "L2 informatique groupe 2 - UPPA\n");
}

bool nbValide(int input, int limitDown, int limitUp) {
    return input <= limitUp && input >= limitDown;
}

void parseOptions(int argc, char *argv[], int *numberOfQuestionsToAsk, int *numberOfAnswerOptions) {
    opterr = 0;  // Désactiver les messages d'erreur automatiques de getopt_long

    struct option long_opt[] = {{"help", no_argument, NULL, 'h'},
                                {"rules", no_argument, NULL, 'r'},
                                {"student", no_argument, NULL, 's'},
                                {"answers", required_argument, NULL, 'a'},
                                {"questions", required_argument, NULL, 'q'},
                                {NULL, 0, NULL, 0}};

    int opt, optargInt;

    while ((opt = getopt_long(argc, argv, SHORT_OPT, long_opt, NULL)) != -1) {
        switch (opt) {
            case 'h':
                functionHelp();
                exit(EXIT_SUCCESS);

            case 'r':
                functionRules();
                exit(EXIT_SUCCESS);

            case 's':
                functionStudent();
                exit(EXIT_SUCCESS);

            case 'a':

                optargInt = atoi(optarg);
                if (nbValide(optargInt, 2, 4)) {
                    *numberOfAnswerOptions = optargInt;
                } else {
                    fprintf(stderr,
                            "Invalid number of answers. Please choose a number between 2 and 4.\n");
                    exit(EXIT_FAILURE);
                }
                break;

            case 'q':

                optargInt = atoi(optarg);
                if (nbValide(optargInt, 4, 10)) {
                    *numberOfQuestionsToAsk = optargInt;
                } else {
                    fprintf(
                        stderr,
                        "Invalid number of questions. Please choose a number between 4 and 10.\n");
                    exit(EXIT_FAILURE);
                }
                break;

            case '?':
                if (optopt == 'a') {
                    fprintf(stderr, "Option -a/--answers requires a numerical argument.\n");

                } else if (optopt == 'q') {
                    fprintf(stderr, "Option -q/--questions requires a numerical argument.\n");

                } else {
                    fprintf(stderr, "Unknown option `-%c'.\n", optopt);
                }
                exit(EXIT_FAILURE);

            default:
                fprintf(stderr, "Unhandled option `-%c'.\n", opt);
                exit(EXIT_FAILURE);
        }
    }

    if (optind < argc) {
        fprintf(stderr, "Invalid usage: Non-option arguments found.\n");
        USAGE(argv[0]);
        exit(EXIT_FAILURE);
    }
}
