/**
 * @file condorcet_schulze.c
 * @author Gineste Jarod
 * @brief Implémentation des fonctions liées à la méthode de Condorcet Schulze.
 * @date 2023-12-14
 */

#include "condorcet.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>


/**
 * @brief Fonction pour trouver le minimum non traité dans la matrice des duels.
 * @param duelsMatrice Matrice des résultats des duels entre les candidats.
 * @param NB_DUELS Nombre total de duels.
 * @param i_min Pointeur vers l'indice du candidat.
 * @param x_min Pointeur vers l'indice de l'opposant.
 * @param min Pointeur vers la valeur minimale.
 */
void trouverMinimumNonTraite(int **duelsMatrice, int NB_DUELS, int *i_min, int *x_min, int *min) {
    *min = INT_MAX;
    *i_min = -1;
    *x_min = -1;

    for (int i = 0; i < NB_CANDIDAT; i++) {
        for (int x = 0; x < NB_DUELS; x++) {
            if (duelsMatrice[i][x] > 0 && duelsMatrice[i][x] < *min) {
                *i_min = i;
                *x_min = x;
                *min = duelsMatrice[i][x];
            }
        }
    }
}


/**
 * @brief Fonction pour marquer le minimum comme traité (mettre à 0).
 * @param duelsMatrice Matrice des résultats des duels entre les candidats.
 * @param i_min Indice du candidat.
 * @param x_min Indice de l'opposant.
 */
void marquerMinimumTraite(int **duelsMatrice, int i_min, int x_min) {
    if (i_min != -1 && x_min != -1) {
        duelsMatrice[i_min][x_min] = 0;
    }
}


/**
 * @brief Fonction pour vérifier si une colonne a que des 0.
 * @param duelsMatrice Matrice des résultats des duels entre les candidats.
 * @param NB_CANDIDAT Nombre total de candidats.
 * @param opposant Indice de l'opposant.
 * @param NB_DUELS Nombre total de duels.
 * @return 1 si la colonne a que des 0, sinon 0.
 */
int colonneAQueDesZeros(int **duelsMatrice, int NB_CANDIDAT, int opposant, int NB_DUELS) {
    for (int candidat = 0; candidat < NB_CANDIDAT; candidat++) {
        if (duelsMatrice[candidat][opposant] != 0) {
            return 0;
        }
    }
    return 1;
}


/**
 * @brief Fonction principale pour trouver le gagnant avec la méthode de Schulze.
 * @param duelsMatrice Matrice des résultats des duels entre les candidats.
 * @param fichierLog Fichier de log.
 * @param NB_DUELS Nombre total de duels.
 * @return l'indice du gagnant s'il y a un gagnant de Schulze, sinon -1.
 */
int condorcetSchulze(int **duelsMatrice, const char *fichierLog, int NB_DUELS) {

    FILE * fptr;
    fptr = fopen(fichierLog, "a");
    fprintf(fptr,"\nCONDORCET SCHULZE\n");
    
    // Création d'une copie locale de la matrice pour éviter les modifications
    int **duelsMatriceCopy = malloc(NB_CANDIDAT * sizeof(int *));
    for (int i = 0; i < NB_CANDIDAT; i++) {
        duelsMatriceCopy[i] = malloc(NB_DUELS * sizeof(int));
        for (int j = 0; j < NB_DUELS; j++) {
            duelsMatriceCopy[i][j] = duelsMatrice[i][j];
        }
    }

    int gagnant = -1;

    while (gagnant == -1) {
        int min, i_min, x_min;
        trouverMinimumNonTraite(duelsMatriceCopy, NB_DUELS, &i_min, &x_min, &min);
        fprintf(fptr,"Minimum trouvé : ligne - %d / colonne - %d / poid arc supprimé - %d\n",i_min,x_min,min);
        marquerMinimumTraite(duelsMatriceCopy, i_min, x_min);

        // Vérifier s'il y a une colonne avec que des 0
        int count = 0;
        for (int opposant = 0; opposant < NB_DUELS; opposant++) {
            if (colonneAQueDesZeros(duelsMatriceCopy, NB_CANDIDAT, opposant, NB_DUELS)) {
                count++;
            }
        }

        // Si une colonne a tous les 0, on a trouvé le gagnant
        if (count > 0) {
            gagnant = x_min;
        }
    }
    fprintf(fptr,"Indice du gagnant -> %d\n",gagnant);

    // Libération de la mémoire allouée pour la copie locale
    for (int i = 0; i < NB_CANDIDAT; i++) {
        free(duelsMatriceCopy[i]);
    }
    free(duelsMatriceCopy);
    fclose(fptr);

    return gagnant;
}
