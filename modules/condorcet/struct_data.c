#include "struct_data.h"

// Fonction pour initialiser une matrice dynamique
void initialiserMatrice(MatriceDynamique *matriceDyn, int nbCandidats, int nbDuels) {
    matriceDyn->nbCandidats = nbCandidats;
    matriceDyn->nbDuels = nbDuels;

    matriceDyn->matrice = malloc(nbCandidats * sizeof(int **));
    for (int i = 0; i < nbCandidats; i++) {
        matriceDyn->matrice[i] = malloc(nbDuels * sizeof(int*));
        for (int j = 0; j < nbDuels; j++) {
            matriceDyn->matrice[i][j] = (int *)calloc(2, sizeof(int));
        }
    }
}

// Fonction pour libérer la mémoire de la matrice dynamique
void libererMatrice(MatriceDynamique *matriceDyn) {
    for (int i = 0; i < matriceDyn->nbCandidats; i++) {
        free(matriceDyn->matrice[i]);
    }
    free(matriceDyn->matrice);
}



int NB_DUELS = NB_CANDIDAT - 1;  // Initialisation de la constante
const char *burgers[10] = {"Burger Black Pepper", "Burger Sud-Ouest", "Thai Burger", "Veggie Burger", "Fire cracker", "Roma", "Crispy", "Cheese Burger", "Burger surprise", "Country"};  // Initialisation de la constante
