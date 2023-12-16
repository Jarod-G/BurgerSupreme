#include "condorcet.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Structure pour représenter un duel entre deux candidats
typedef struct {
    int candidat1;
    int candidat2;
} Duel;

// Fonction pour créer une matrice des duels à partir des scores des candidats
void creerMatriceDuels(int scores[NB_CANDIDAT][NB_CANDIDAT], Duel matriceDuels[NB_CANDIDAT * (NB_CANDIDAT - 1) / 2]) {
    int index = 0;
    for (int i = 0; i < NB_CANDIDAT; i++) {
        for (int j = i + 1; j < NB_CANDIDAT; j++) {
            matriceDuels[index].candidat1 = i;
            matriceDuels[index].candidat2 = j;
            index++;
        }
    }
}

// Fonction pour trouver le gagnant d'un duel
int trouverGagnantDuel(int scores[NB_CANDIDAT][NB_CANDIDAT], Duel duel) {
    if (scores[duel.candidat1][duel.candidat2] > scores[duel.candidat2][duel.candidat1]) {
        return duel.candidat1;
    } else {
        return duel.candidat2;
    }
}

// Fonction pour créer le graphe des duels en utilisant la méthode Condorcet par paires
void creerGrapheDuels(int scores[NB_CANDIDAT][NB_CANDIDAT], int grapheDuels[NB_CANDIDAT][NB_CANDIDAT]) {
    Duel matriceDuels[NB_CANDIDAT * (NB_CANDIDAT - 1) / 2];
    creerMatriceDuels(scores, matriceDuels);

    for (int i = 0; i < NB_CANDIDAT; i++) {
        for (int j = i + 1; j < NB_CANDIDAT; j++) {
            int gagnant = trouverGagnantDuel(scores, matriceDuels[i * (NB_CANDIDAT - 1) / 2 + j - (i + 1)]);
            grapheDuels[i][j] = gagnant;
        }
    }
}

// Fonction pour trouver le gagnant du graphe des duels en utilisant la méthode Condorcet par paires
int trouverGagnantCondorcetPaires(int grapheDuels[NB_CANDIDAT][NB_CANDIDAT]) {
    int gagnant;
    for (int i = 0; i < NB_CANDIDAT; i++) {
        int compteGagnant = 0;
        for (int j = 0; j < NB_CANDIDAT; j++) {
            if (grapheDuels[j][i] == i) {
                compteGagnant++;
            }
        }
        if (compteGagnant == NB_CANDIDAT - 1) {
            gagnant = i;
            break;
        }
    }
    return gagnant;
}


