#include "struct_data.h"

// Fonction pour initialiser une matrice dynamique
void initialiserMatrice(MatriceDynamique *matriceDyn, int nbCandidats, int nbDuels) {
    matriceDyn->nbCandidats = nbCandidats;
    matriceDyn->nbDuels = nbDuels;

    // Allocation de la mémoire pour la matrice
    matriceDyn->matrice = (int ***)malloc(nbCandidats * sizeof(int **));
    for (int i = 0; i < nbCandidats; i++) {
        matriceDyn->matrice[i] = (int **)malloc(nbCandidats * sizeof(int *));
        for (int j = 0; j < 2; j++) {
            matriceDyn->matrice[i][j] = (int *)malloc(nbDuels * sizeof(int));
        }
    }
}

// Fonction pour libérer la mémoire de la matrice dynamique
void libererMatrice(MatriceDynamique *matriceDyn) {
    for (int i = 0; i < matriceDyn->nbCandidats; i++) {
        for (int j = 0; j < matriceDyn->nbCandidats; j++) {
            free(matriceDyn->matrice[i][j]);
        }
        free(matriceDyn->matrice[i]);
    }
    free(matriceDyn->matrice);
}


int NB_DUELS = NB_CANDIDAT - 1;  // Initialisation de la constante
const char *burgers[10] = {"Burger Black Pepper", "Burger Sud-Ouest", "Thai Burger", "Veggie Burger", "Fire cracker", "Roma", "Crispy", "Cheese Burger", "Burger surprise", "Country"};  // Initialisation de la constante
