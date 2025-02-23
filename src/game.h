#ifndef GAME_H
#define GAME_H

#include "../include/quiz.h"

/**
 * Exécute la boucle principale du jeu dans le processus fils.
 * Cette fonction sélectionne un ensemble de questions aléatoirement, les envoie au processus père,
 * attend les réponses, vérifie ces réponses, et met à jour le score dans la mémoire partagée.
 * 
 * @param questionPipeW Descripteur de fichier pour l'écriture dans le pipe des questions, utilisé pour envoyer les questions au processus père.
 * @param answerPipeR Descripteur de fichier pour la lecture dans le pipe des réponses, utilisé pour recevoir les réponses du processus père.
 * @param shm_id Identifiant de la mémoire partagée utilisée pour stocker et accéder au score du jeu.
 * @param numberOfQuestionsToAsk Nombre de questions à poser durant la session du jeu.
 * @param numberOfOptions Nombre d'options à afficher pour chaque question.
 */
void gameLoop(int questionPipeW, int answerPipeR, int shm_id, int numberOfQuestionsToAsk, int numberOfOptions);

/**
 * Met à jour le score du joueur dans la mémoire partagée.
 * Le score est incrémenté de 1 si la réponse est correcte.
 * 
 * @param shm_id Identifiant de la mémoire partagée où le score est stocké.
 * @param correct Booléen indiquant si la dernière réponse était correcte ou non.
 */
void updateScore(int shm_id, bool correct);

/**
 * Vérifie le score final du joueur enregistré dans la mémoire partagée
 * et détermine le résultat du jeu (succès ou échec).
 * 
 * Cette fonction calcule le pourcentage de réponses correctes en fonction du score 
 * et du nombre total de questions. Elle utilise ensuite ce pourcentage pour déterminer 
 * si le joueur a gagné ou perdu. Selon le résultat, elle lance un processus enfant 
 * exécutant le programme `success` ou `failure`.
 * 
 * @param shm_id L'identifiant de la mémoire partagée où le score est stocké.
 * @param totalQuestions Le nombre total de questions posées au joueur.
 * 
 * Le processus enfant créé exécute `success` si le pourcentage de réussite est 
 * supérieur ou égal à 50%, sinon il exécute `failure`. Le processus parent attend 
 * que le processus enfant termine avant de continuer.
 */
void checkWinLoss(int shm_id, int totalQuestions);

/**
 * Mélange les options de réponse d'une question et s'assure que le choix valide est inclus.
 * Cette fonction crée une nouvelle instance de la structure mcq_t contenant la question
 * originale et un ensemble mélangé d'options de réponse. Le nombre d'options à inclure
 * et à afficher est déterminé par le paramètre numOptions.
 * 
 * @param question Pointeur vers la structure mcq_t contenant la question et les options originales.
 * @param numOptions Nombre d'options de réponse à inclure dans la question mélangée. Doit être entre 2 et 4.
 * @return Pointeur vers une nouvelle structure mcq_t avec les options mélangées, ou NULL en cas d'erreur.
 * 
 * La fonction procède comme suit :
 * 1. Vérifie que numOptions est dans l'intervalle valide (entre 2 et 4).
 * 2. Alloue une nouvelle structure mcq_t pour contenir la question avec les options mélangées.
 * 3. Copie la question originale dans la nouvelle structure.
 * 4. Sélectionne la réponse valide et jusqu'à trois autres options de manière aléatoire,
 *    en s'assurant qu'il n'y a pas de doublons et que la réponse valide est toujours incluse.
 * 5. Mélange les options sélectionnées pour randomiser leur ordre d'affichage.
 * 6. Affecte les options mélangées à la nouvelle structure et ajuste le champ validChoice
 *    pour refléter la position de la réponse valide dans les options mélangées.
 * 7. Renvoie un pointeur vers la nouvelle structure contenant la question et les options mélangées.
 */
mcq_t* shuffleOptions(mcq_t *question, int numOptions);

#endif