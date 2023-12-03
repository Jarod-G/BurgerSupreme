/**
 * @file condorcet_schulze.c
 * @author Gineste Jarod
 * @brief this file gives functions to find the winner of the Condorcet Schulze election
 * @version 0.1
 * @date 2023-11-25
 */


#include "../utils/struct_data.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void condorcetSchulze(int **duelsMatrice) {
    int strength[NB_CANDIDAT][NB_CANDIDAT];

    // Initialiser la matrice de force à 0
    for (int i = 0; i < NB_CANDIDAT; i++) {
        for (int j = 0; j < NB_CANDIDAT; j++) {
            strength[i][j] = 0;
        }
    }

    // Calculer la matrice de force
    for (int i = 0; i < NB_CANDIDAT; i++) {
        for (int j = 0; j < NB_CANDIDAT; j++) {
            if (i != j) {
                for (int k = 0; k < NB_CANDIDAT - 1; k++) {
                    if (duelsMatrice[i][k] > duelsMatrice[j][k]) {
                        strength[i][j]++;
                    }
                }
            }
        }
    }

    // Trouver le gagnant du vote Condorcet Schulze
    for (int candidat = 0; candidat < NB_CANDIDAT; candidat++) {
        int estGagnant = 1;  // Supposons initialement que le candidat est le gagnant

        for (int adversaire = 0; adversaire < NB_CANDIDAT; adversaire++) {
            if (candidat != adversaire && strength[candidat][adversaire] < strength[adversaire][candidat]) {
                estGagnant = 0;  // Le candidat a perdu face à au moins un adversaire
                break;
            }
        }

        if (estGagnant) {
            printf("Le gagnant du vote Condorcet Schulze est %s\n", burgers[candidat]);
            break;
        }
    }

}

void ensembleSchwartz(int **duelsMatrice, int schwartzSet[NB_CANDIDAT]) {
    int hasEdges = 1;

    while (hasEdges) {
        // Vérifier s'il reste des arcs dans le graphe (matrice)
        hasEdges = 0;

        // Éliminer les sommets qui n'appartiennent pas à l'ensemble de Schwartz
        for (int i = 0; i < NB_DUELS; i++) {
            for (int j = 0; j < NB_DUELS; j++) {
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

void condorcetSchulzeSchwartz(int **duelsMatrice) {
    int *schwartzSet = (int*) malloc(NB_DUELS * sizeof(int));

    // Initialisez le tableau avec des 1
    for (int i = 0; i < NB_DUELS; i++) {
        schwartzSet[i] = 1;
    }

    ensembleSchwartz(duelsMatrice, schwartzSet);

    // Trouver le gagnant du vote Condorcet Schulze
    for (int i = 0; i < NB_DUELS; i++) {
        if (schwartzSet[i]) {
            printf("Le gagnant du vote Condorcet Schulze Schwartz est %s\n", burgers[i]);
            break;
        }
    }
    free(schwartzSet);
}
