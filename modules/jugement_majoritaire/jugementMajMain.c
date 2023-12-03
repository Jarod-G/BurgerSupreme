/**
 * @file jugementMajoritaire.c
 * @author Handwerk Hippolyte
 * @author Gineste Jarod
 * @brief this function gives the winner of the Majority judgment
 * @version 0.1
 * @date 2022-12-03
 */

#include "../utils/lecture_csv.h"
#include "../utils/lecture_csv.c"
#include "../utils/struct_data.h"
#include "jugementMajoritaire.c"
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


int main(int argc, char const *argv[])
{
    voteElecteur **v_elect = malloc(MAX_VOTES_E * sizeof(voteElecteur));
    nbElecteurs *nb_elect = malloc(sizeof(nbElecteurs));

    char* fichierBallots = "/home/jarod/Documents/projet/BurgerSupreme/data/jugement.csv";
    lireFichierCSV_vote(fichierBallots, v_elect, nb_elect);

    printf("\nRecherche d'un gagnant avec la méthode jugement majoritaire :\n");
    int i;
    for (i = 0; i <= 100; i++) {
        afficherBarreDeChargement(i);
        usleep(20000);  // Simule un travail en attente
    }

    printf("\nGagnant trouvé\n\n");
    jugementMajoritaire(v_elect,nb_elect->nb_electeur,NB_CANDIDAT);
    free(v_elect);
    free(nb_elect);
    
    return 0;
}
