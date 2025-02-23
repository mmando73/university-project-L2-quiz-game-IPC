#include "../include/quiz.h"

#define SHORT_OPT "hrsa:q:"
#define USAGE_FMT  "%s [-h help] [-r rules] [-s student] [-a answers] [-q questions]"

// Macro pour afficher l'usage
#define USAGE(programName) printf(USAGE_FMT "\n", programName);

// Affichage du message dans help
void functionHelp();

// Affichage des règles du jeu
void functionRules();

// Affichage du nom des étudiants
void functionStudent();

// Vérification si l'argument entré est bien entre les valeurs préconisées
bool nbValide(int input, int limitDown, int limitUp);

/**
 * Parse les options de ligne de commande fournies au programme.
 * 
 * Cette fonction analyse les arguments passés au programme et définit les valeurs
 * pour le nombre de questions à poser et le nombre d'options de réponse basé sur
 * les options de ligne de commande spécifiées par l'utilisateur. Les options supportées
 * incluent l'affichage de l'aide, des règles du jeu, des informations sur les étudiants,
 * ainsi que la définition du nombre de questions et du nombre d'options de réponse.
 * 
 * @param argc Le nombre d'arguments de la ligne de commande passés au programme.
 * @param argv Le tableau des arguments de la ligne de commande passés au programme.
 * @param numberOfQuestionsToAsk Un pointeur vers un entier où le nombre de questions à poser sera stocké.
 * @param numberOfAnswerOptions Un pointeur vers un entier où le nombre d'options de réponse sera stocké.
 * 
 * La fonction ajuste les valeurs pointées par numberOfQuestionsToAsk et numberOfAnswerOptions
 * en fonction des options -q/--questions et -a/--answers. En cas d'option -h/--help, -r/--rules,
 * ou -s/--student, la fonction affiche les informations correspondantes et termine le programme.
 * Si les options fournies sont invalides ou si les arguments sont incorrects (par exemple,
 * fournir un argument non numérique pour -a ou -q), la fonction affiche un message d'erreur
 * et termine le programme.
 */
void parseOptions(int argc, char *argv[], int *numberOfQuestionsToAsk, int *numberOfAnswerOptions);