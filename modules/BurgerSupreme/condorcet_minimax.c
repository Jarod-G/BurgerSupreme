/**
 * @file condorcet.c
 * @author Handwerk Hippolyte
 * @brief Implémentation des fonctions liées à la méthode de Condorcet minimax.
 * @version 0.1
 * @date 2023-12-14
 */

#include "condorcet.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * @brief Trouve le vainqueur en utilisant la méthode Condorcet Minimax.
 *
 * Cette fonction prend une matrice de résultats de duels et détermine le vainqueur
 * en fonction de la méthode Condorcet Minimax.
 *
 * @param duelsMatrice La matrice des résultats des duels.
 * @return L'indice du vainqueur.
 */
int condorcetMinimax(int **duelsMatrice) {
    int NB_DUELS = NB_CANDIDAT - 1;
    int minLocal = duelsMatrice[0][0];
    int meilleurmin = duelsMatrice[0][0];
    int posVainqueur = 0;

    // Parcours de chaque candidat
    for (int candidat = 0; candidat < NB_CANDIDAT; candidat++) {
        // Parcours de chaque duel pour un candidat donné
        for (int duel = 0; duel < NB_DUELS; duel++) {
            // Recherche du minimum local pour le candidat actuel
            if (minLocal > duelsMatrice[candidat][duel]) {
                minLocal = duelsMatrice[candidat][duel];
            }
        }

        // Mise à jour du minimum global et de la position du vainqueur
        if (minLocal < meilleurmin) {
            meilleurmin = minLocal;
            posVainqueur = candidat;
        }
    }

    // Retourne l'indice du vainqueur
    return posVainqueur;
}
