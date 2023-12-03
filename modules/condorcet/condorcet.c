/**
 * @file condorcet.c
 * @author Gineste Jarod
 * @brief this is the main file to test different condorcet methodes functions
 * @version 0.1
 * @date 2023-11-25
 */
#include "../utils/struct_data.h"
#include "../utils/lecture_csv.h"
#include "../utils/lecture_csv.c"
#include "condorcet_utils.c"
#include "condorcet_schulze.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


void afficherBarreDeChargement(int pourcentage) {
    int i;
    const int largeur = 50;
    int nbBarres = pourcentage * largeur / 100;

    printf("[");
    for (i = 0; i < nbBarres; i++) {
        printf("#");
    }
    for (; i < largeur; i++) {
        printf(" ");
    }
    printf("] %d%%\r", pourcentage);
    fflush(stdout);
}


int main(int argc, char* argv[]) {
    voteElecteur **v_elect = malloc(MAX_VOTES_E * sizeof(voteElecteur));
    nbElecteurs *nb_elect = malloc(sizeof(nbElecteurs));

    char* fichierBallots = "/home/jarod/Documents/projet/BurgerSupreme/data/VoteCondorcet.csv";

    lireFichierCSV_vote(fichierBallots, v_elect, nb_elect);

    // Allouez de la mémoire pour la matrice dynamique
    int **matriceDynamique = malloc(NB_CANDIDAT * sizeof(int *));
    for (int i = 0; i < NB_CANDIDAT; i++) {
        matriceDynamique[i] = malloc(NB_DUELS * sizeof(int));
    }

    // Initialisez la matrice avec des valeurs
    for (int i = 0; i < NB_CANDIDAT; i++) {
        for (int j = 0; j < NB_DUELS; j++) {
            matriceDynamique[i][j] = 0;
        }
    }

    duelsCalculs(v_elect, nb_elect->nb_electeur, matriceDynamique);

    printf("\nRecherche d'un gagnant avec les différentes méthodes de condorcet :\n");
    int i;
    for (i = 0; i <= 100; i++) {
        afficherBarreDeChargement(i);
        usleep(20000);  // Simule un travail en attente
    }

    printf("\nGagnant trouvé\n\n");

    condorcet(matriceDynamique);
    condorcetSchulze(matriceDynamique);
    condorcetSchulzeSchwartz(matriceDynamique);

    for (int i = 0; i < NB_CANDIDAT; i++) {
        free(matriceDynamique[i]);
    }

    free(matriceDynamique);
    free(v_elect);
    free(nb_elect);

    return 0;
}