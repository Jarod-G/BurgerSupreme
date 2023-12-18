/**
 * @file condorcet_paires.c
 * @brief Fonctions pour la méthode de Condorcet avec résolution du paradoxe.
 * @author Barcelo Fanny
 */

#include "condorcet.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


// Structure pour représenter un duel entre deux candidats
typedef struct {
    int candidat1;
    int candidat2;
    int poids;
} Duel;


/**
 * @brief Compare deux duels pour le tri.
 * @param a Premier duel.
 * @param b Deuxième duel.
 * @return Valeur négative si le poids de b est plus grand que celui de a, sinon, une valeur positive.
 */
int comparerDuels(const void *a, const void *b) {
    return ((Duel *)b)->poids - ((Duel *)a)->poids;
}


/**
 * @brief Crée une matrice des duels à partir des scores des candidats.
 * @param matrice Matrice des scores des candidats.
 * @param matriceDuels Tableau de duels à remplir.
 */
void creerMatriceDuels(int **matrice, Duel matriceDuels[NB_CANDIDAT * (NB_CANDIDAT - 1) / 2]) {
    int index = 0;
    for (int i = 0; i < NB_CANDIDAT; i++) {
        for (int j = i + 1; j < NB_CANDIDAT; j++) {
            matriceDuels[index].candidat1 = i;
            matriceDuels[index].candidat2 = j;
            matriceDuels[index].poids = matrice[i][j] - matrice[j][i];
            index++;
        }
    }
}


/**
 * @brief Trouve le gagnant d'un duel.
 * @param matrice Matrice des scores des candidats.
 * @param duel Duel à évaluer.
 * @return Identifiant du candidat gagnant.
 */

int trouverGagnantDuel(int **matrice, Duel duel) {
    if (matrice[duel.candidat1][duel.candidat2] > matrice[duel.candidat2][duel.candidat1]) {
        return duel.candidat1;
    } else {
        return duel.candidat2;
    }
}


/**
 * @brief Trouve le gagnant selon la méthode de Condorcet avec résolution du paradoxe.
 * @param matrice Matrice des scores des candidats.
 * @param fichierLog Fichier de log.
 * @return Identifiant du candidat gagnant.
 */
int CondorcetAvecResolution(int **matrice,const char* fichier_log) {

    FILE * fptr;
    fptr = fopen(fichier_log, "a");
    fprintf(fptr,"\nCONDORCET PAIRES\n");

    // Créer une matrice des duels
    Duel matriceDuels[NB_CANDIDAT * (NB_CANDIDAT - 1) / 2];
    creerMatriceDuels(matrice, matriceDuels);

    // Trier la matrice des duels par poids décroissant
    qsort(matriceDuels, NB_CANDIDAT * (NB_CANDIDAT - 1) / 2, sizeof(Duel), comparerDuels);
    
    // Tableau pour indiquer si un arc est confirmé
    int *arcConfirme = malloc(NB_CANDIDAT * NB_CANDIDAT * sizeof(int));
    for (int i = 0; i < NB_CANDIDAT * NB_CANDIDAT; i++) {
        arcConfirme[i] = 0;
    }

    // Parcourir la matrice des duels
    for (int i = 0; i < NB_CANDIDAT * (NB_CANDIDAT - 1) / 2; i++) {
        int gagnant = trouverGagnantDuel(matrice, matriceDuels[i]);

        // Vérifier s'il y a un cycle
        if (!arcConfirme[matriceDuels[i].candidat1 * NB_CANDIDAT + gagnant] &&
            !arcConfirme[matriceDuels[i].candidat2 * NB_CANDIDAT + gagnant]) {
            // Confirmer l'arc
            arcConfirme[matriceDuels[i].candidat1 * NB_CANDIDAT + matriceDuels[i].candidat2] = 1;
            arcConfirme[matriceDuels[i].candidat2 * NB_CANDIDAT + gagnant] = 1;
        }
    }

    fprintf(fptr, "Matrice arcConfirme : \n");
    for (int i = 0; i < NB_CANDIDAT; i++) {
        for (int j = 0; j < NB_CANDIDAT; j++) {
            fprintf(fptr, "%d ", arcConfirme[i * NB_CANDIDAT + j]);
        }
        fprintf(fptr, "\n");
    }

    // Trouver le gagnant
    int gagnant = -1;
    for (int i = 0; i < NB_CANDIDAT; i++) {
        int candidatGagnant = 1;
        for (int j = 0; j < NB_CANDIDAT; j++) {
            if (i != j && !arcConfirme[j * NB_CANDIDAT + i]) {
                candidatGagnant = 0;
                break;
            }
        }
        if (candidatGagnant) {
            gagnant = i;
            break;
        }
    }

    fprintf(fptr, "gagnant : %d\n",gagnant);

    // Libérer la mémoire
    free(arcConfirme);
    fclose(fptr);
    return gagnant;
}


/**
 * @brief Trouve le gagnant selon la méthode de Condorcet avec résolution du paradoxe (fonction d'interface).
 * @param matrice Matrice des scores des candidats.
 * @param fichierLog Fichier de log.
 * @return Identifiant du candidat gagnant.
 */
int condorcetPaires(int **matrice,const char* fichier_log){
    return CondorcetAvecResolution(matrice, fichier_log) + 1;
}