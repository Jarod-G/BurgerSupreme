/**
 * @file condorcet_schulze.c
 * @author Gineste Jarod
 * @brief Implémentation des fonctions liées à la méthode de Condorcet Schulze.
 * @version 0.1
 * @date 2023-12-14
 */

#include "condorcet.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * @brief Élimine les candidats non inclus dans l'ensemble de Schwartz.
 * @param duelsMatrice Matrice des résultats des duels entre les candidats.
 * @param schwartzSet Tableau représentant l'ensemble de Schwartz.
 */
void ensembleSchwartz(int **duelsMatrice, int schwartzSet[NB_CANDIDAT]) {
    int hasEdges = 1;

    // Continuer tant qu'il reste des arcs dans le graphe
    while (hasEdges) {
        // Vérifier s'il reste des arcs dans le graphe (matrice)
        hasEdges = 0;

        // Éliminer les sommets qui n'appartiennent pas à l'ensemble de Schwartz
        for (int i = 0; i < NB_CANDIDAT; i++) {
            for (int j = 0; j < NB_CANDIDAT; j++) {
                if (i != j && schwartzSet[i] && schwartzSet[j]) {
                    if (duelsMatrice[i][j] < duelsMatrice[j][i]) {
                        hasEdges = 1;
                        schwartzSet[i] = 0; // Éliminer le candidat i
                    }
                }
            }
        }
    }
}

/**
 * @brief Applique la méthode Condorcet Schulze Schwartz pour déterminer le gagnant du vote.
 * @param duelsMatrice Matrice des résultats des duels entre les candidats.
 * @return L'indice du gagnant du vote Condorcet Schulze ou -1 s'il n'y en a pas.
 */
int condorcetSchulze(int **duelsMatrice) {
    // Initialiser l'ensemble de Schwartz
    int *schwartzSet = malloc(NB_CANDIDAT * sizeof(int));

    for (int i = 0; i < NB_CANDIDAT; i++) {
        schwartzSet[i] = 1;
    }

    // Appliquer la méthode de Schwartz
    ensembleSchwartz(duelsMatrice, schwartzSet);

    // Trouver le gagnant du vote Condorcet Schulze
    for (int i = 0; i < NB_CANDIDAT; i++) {
        if (schwartzSet[i]) {
            free(schwartzSet);
            return i;
        }
    }

    // Libérer la mémoire allouée pour l'ensemble de Schwartz
    free(schwartzSet);

    // Aucun gagnant trouvé
    return -1;
}
