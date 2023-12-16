/**
 * @file jugementMajoritaire.c
 * @brief Fonctions pour déterminer le gagnant selon le jugement majoritaire
 * @author Handwerk Hippolyte
 * @author Gineste Jarod
 * @version 0.1
 * @date 2023-12-14
 */

#include "jugementMajoritaire.h"
#include "lecture_csv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const char *nomAppreciation[6] = {"Très Bien" , "Bien" , "Assez Bien" , "Passable", "Insuffisant","À Rejeter"};

/**
 * @brief Fonction qui calcule l'appréciation d'un candidat
 * @param votes Tableau des votes des électeurs
 * @param numCandidat Numéro du candidat en cours d'évaluation
 * @param nbVotants Nombre total d'électeurs
 * @param fptr Pointeur vers le fichier de sortie
 * @return Tableau de deux floats [appreciation, score]
 */
float * appreciationCandidat(voteElecteur **votes, int numCandidat, int nbVotants, FILE *fptr) {
    float * tab = malloc(6 * sizeof(float)); // on compte les votes en fonction de l'appreciation
    float * appCandidat = malloc(2 * sizeof(float));

    // Initialiser le tableau et appCandidat à zéro
    memset(tab, 0, 6 * sizeof(float));
    memset(appCandidat, 0, 2 * sizeof(float));

    float median;
    int appreciation = 0; // on va chercher le point median 

    // Compter les votes pour chaque appréciation
    for (int i = 0 ; i < nbVotants; i++) {
        if (votes[i]->votes_electeur[numCandidat] != -1) {
            tab[votes[i]->votes_electeur[numCandidat] - 1] += 1.0;
        }
    }

    fprintf(fptr, "%s - ", burgers[numCandidat]);
    
    median = (float)nbVotants / 2;
    for (int i = 0; i < 6; i++) {
        fprintf(fptr, "%s %d voix (%.2f %%)||", nomAppreciation[i], (int)tab[i], (tab[i] / nbVotants) * 100);
    }
    
    fprintf(fptr, "\n");

    // Trouver le point median
    while (median > 0) {
        median -= tab[appreciation++];
    }

    // Récupérer le score de la catégorie du point median
    float scoreMedian = tab[--appreciation];
    appCandidat[0] = (float)appreciation;
    appCandidat[1] = scoreMedian;

    free(tab);
    return appCandidat;
}

/**
 * @brief Fonction principale pour le jugement majoritaire
 * @param votes Tableau des votes des électeurs
 * @param nbVotants Nombre total d'électeurs
 * @param nbCandidat Nombre total de candidats
 * @param fichierLog Nom du fichier de sortie
 */
void jugementMajoritaire(voteElecteur **votes, int nbVotants, int nbCandidat, const char *fichierLog) {
    int burgerGagnant = 0;
    float * candidat;
    FILE * fptr;
    fptr = fopen(fichierLog, "w");
    
    fprintf(fptr, "RESULTAT JUGEMENT MAJORITAIRE : \n");
    float * candidatGagnant = appreciationCandidat(votes, 0, nbVotants, fptr);

    for (int i = 1; i < nbCandidat; i++) {
        candidat = appreciationCandidat(votes, i, nbVotants, fptr);
        if ((candidat[0] < candidatGagnant[0]) || (candidat[0] == candidatGagnant[0] && candidat[1] > candidatGagnant[1])) {
            candidatGagnant = candidat;
            burgerGagnant = i;
        }
    }

    fprintf(fptr, "Le gagnant est %s avec la mention %s (%.2f %%) \n", burgers[burgerGagnant], nomAppreciation[(int)candidatGagnant[0]], (candidatGagnant[1] / nbVotants) * 100);
    printf("Le gagnant est %s avec la mention %s (%.2f %%) \n", burgers[burgerGagnant], nomAppreciation[(int)candidatGagnant[0]], (candidatGagnant[1] / nbVotants) * 100);
    free(candidat);
}

/**
 * @brief Fonction principale du programme
 * @return 0 si l'exécution est réussie
 */
int main(int argc, char* argv[]) {
    voteElecteur **v_elect = malloc(MAX_VOTES_E * sizeof(voteElecteur));
    nbElecteurs *nb_elect = malloc(sizeof(nbElecteurs));
    if(argc != 3){
        printf("Usage : %s <FichierBallots> <Fichier_log>\n", argv[0]);
    }
    char* fichierBallots = "/home/jarod/Documents/projet/BurgerSupreme/data/jugement.csv";
    const char *fichierLog = argv[2];
    lireFichierCSV_vote(fichierBallots, v_elect, nb_elect);
    printf("Gagnant trouvé avec la méthode du jugement Majoritaire :\n");
    jugementMajoritaire(v_elect, nb_elect->nb_electeur, NB_CANDIDAT, fichierLog);
    free(v_elect);
    free(nb_elect);
    
    return 0;
}