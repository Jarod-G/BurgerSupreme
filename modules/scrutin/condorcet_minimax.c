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
int condorcetMinimax(int **duelsMatrice, const char * fichierLog) {
    int NB_DUELS = NB_CANDIDAT - 1;
    int minLocal = duelsMatrice[0][0];
    int meilleurmin = duelsMatrice[0][1];
    int posVainqueur = 0;
    int minEnCours=duelsMatrice[0][1];
    FILE * fptr;
    fptr = fopen(fichierLog, "a");
    fprintf(fptr,"\nRESULTAT CONDORCET MINIMAX\n");
    // Parcours de chaque candidat
    for (int candidat = 0; candidat < NB_CANDIDAT; candidat++) {
        // Parcours de chaque duel pour un candidat donné
        for (int duel = 0; duel < NB_DUELS; duel++) {
            if(duel==candidat)
            minEnCours=duelsMatrice[candidat][duel];
            // Recherche du minimum local pour le candidat actuel
            if (minLocal > minEnCours) {
                minLocal = minEnCours;
            }
        }
        fprintf(fptr,"%s : %d |",burgers[candidat],minLocal);

        // Mise à jour du minimum global et de la position du vainqueur
        if (minLocal < meilleurmin) {
            meilleurmin = minLocal;
            posVainqueur = candidat;
        }
    }
    fprintf(fptr,"\n\n");
    fclose(fptr);
    // Retourne l'indice du vainqueur
    return posVainqueur;
}
