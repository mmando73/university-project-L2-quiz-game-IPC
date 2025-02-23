#include "questions.h"

bool startsWith(const char *a, const char *b) {
   if(strncmp(a, b, strlen(b)) == 0) return 1;
   return 0;
}

const char* stripQuestionPrefix(const char *a) {
    int prefixLength = 3; // "Q: " le format utilisé dans le fichier "questions.txt" 
    // On vérifie qu'il existe bien un préfixe avant de continuer
    if (strlen(a) < prefixLength) return NULL;

    return a + prefixLength; // On retourne un pointeur vers la partie du string après le préfixe
}

const char* stripAnswerPrefix(const char *a) {
    int prefixLength = 4; // "A - " le format utilisé dans le fichier "questions.txt" 
    // On vérifie qu'il existe bien un préfixe avant de continuer
    if (strlen(a) < prefixLength) return NULL;

    return a + prefixLength; // On retourne un pointeur vers la partie du string après le préfixe
}
char extractValidChoice(const char *a) {
    // On vérifie que la taille de la chaine est suffisamment longue pour contenir un format de réponse valide.
    if (strlen(a) < ANSWER_POSITION + 1) return '\0'; // Utilisation de '\0' pour indiquer une erreur/une entrée invalide

    // On extrait la lettre de la bonne réponse 
    char c = a[ANSWER_POSITION];
    return c;
}

bool answerCheck(mcq_t question, char answer) {
    return answer == question.validChoice;
}

char* getValidChoiceString(mcq_t q) { 
    char *choiceStr;
    switch(q.validChoice) {
        case 'A': choiceStr = q.A; break;
        case 'B': choiceStr = q.B; break;
        case 'C': choiceStr = q.C; break;
        case 'D': choiceStr = q.D; break;
        default: return "Invalid choice"; // Si in choix est invalide
    }
    return choiceStr; 
}

mcq_t* loadQuestions(){
    FILE *file = fopen("src/questions.txt", "r");
    if (file == NULL) {
        printf("Error opening file\n");
        fprintf(stderr, "ERROR_questions.c: questions.txt is damaged or not available.\n");
        exit(EXIT_FAILURE);
    }

    mcq_t *questions = malloc(ALL_QUESTIONS * sizeof(mcq_t)); 
    if (questions == NULL) {
        fprintf(stderr, "ERROR_questions.c: Memory allocation error in loadQuestions().\n");
        exit(EXIT_FAILURE);
    }
    
    int qIndex = 0;
    char line[256];

    while (fgets(line, sizeof(line), file)) {
        if (startsWith(line, "Q: ")) { //"Q: " le format utilisé dans le fichier "questions.txt" 
            strcpy(questions[qIndex].question, stripQuestionPrefix(line));
            while (fgets(line, sizeof(line), file) != NULL && !startsWith(line, "A - ")) {
                    // On ajoute le reste des lignes de la question jusqu'à arriver à "A - "
                    strcat(questions[qIndex].question, line);
            }
            //Ici la ligne du choix A est déjà lue
            //On enlève le caractère de retour à la ligne '\n' de la ligne lue avant de la récopier
            line[strcspn(line, "\n")]= '\0';
            strcpy(questions[qIndex].A, stripAnswerPrefix(line));

            fgets(line, sizeof(line), file); // Lecture de la ligne du choix B
            //On enlève le caractère de retour à la ligne '\n' de la ligne lue avant de la récopier
            line[strcspn(line, "\n")] = '\0';
            strcpy(questions[qIndex].B, stripAnswerPrefix(line));

            fgets(line, sizeof(line), file); // Lecture de la ligne du choix C
            //On enlève le caractère de retour à la ligne '\n' de la ligne lue avant de la récopier
            line[strcspn(line, "\n")] = '\0';
            strcpy(questions[qIndex].C, stripAnswerPrefix(line));

            fgets(line, sizeof(line), file); // Lecture de la ligne du choix D
            //On enlève le caractère de retour à la ligne '\n' de la ligne lue avant de la récopier
            line[strcspn(line, "\n")] = '\0';
            strcpy(questions[qIndex].D, stripAnswerPrefix(line));

            fgets(line, sizeof(line), file); // Lecture de la ligne du bon choix
            questions[qIndex].validChoice = extractValidChoice(line); // Extraire la lettre correspondante au choix valide

            qIndex++;
        }
    }

    fclose(file);

    return questions;
}

mcq_t* selectRandomQuestions(mcq_t *allQuestions, int allQuestionCount, int selectCount){
     if (selectCount > allQuestionCount) {
        fprintf(stderr, "ERROR_questions.c: the questions count is greater than the maximum (45 MAX).\n");
        exit(EXIT_FAILURE);
    }

    mcq_t *randomQuestions = malloc(selectCount * sizeof(mcq_t));
    if (randomQuestions == NULL) {
        fprintf(stderr, "ERROR_questions.c: Memory allocation error in selectRandomQuestions().\n");
        exit(EXIT_FAILURE);
    }

    bool usedIndices[allQuestionCount];  // Tableau pour suivre les indices utilisés
    memset(usedIndices, 0, sizeof(usedIndices));  // Initialisation du tableau usedIndices à false

    // Le choix aléatoire des questions
    for (int i = 0; i < selectCount; i++){
        int k;
        do {
            k = rand() % allQuestionCount;
        } while (usedIndices[k]);  // On continue à générer une nouvelle indice si celle obtenue est déjà utilisée

        usedIndices[k] = true;  // On marque l'indice comme utilisée
        randomQuestions[i] = allQuestions[k]; // On recopie la question de l'indice obtenue précédament
        }
        
    return randomQuestions;
}

