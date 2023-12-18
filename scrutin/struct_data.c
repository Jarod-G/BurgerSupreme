/**
 * @file struct_data.c
 * @author Gineste Jarod
 * @brief Définition de données structurées et fonctions associées
 * @date 2023-11-28
 * 
 */
#include "struct_data.h"
#include <stdio.h>

/*----------------------------VARS GLOBALS----------------------------*/
int NB_CANDIDAT = 10;
const char *burgers[10] = {"Burger Black Pepper", "Burger Sud-Ouest", "Thai Burger", "Veggie Burger", "Fire cracker", "Roma", "Crispy", "Cheese Burger", "Burger surprise", "Country"};  // Initialisation de la constante
/*--------------------------------------------------------------------*/


/**
 * @brief Initialise une matrice avec des zéros.
 * @param matrice Pointeur vers la structure matriceTab à initialiser
 * @param lignes Nombre de lignes dans la matrice
 * @param colonnes Nombre de colonnes dans la matrice
 */
void initialiserMatrice(matriceTab *matrice, int lignes, int colonnes) {
    // Initialiser le tableau d'entiers
    matrice->tab = malloc(lignes * sizeof(int *));
    for (int i = 0; i < lignes; i++) {
        matrice->tab[i] = malloc(colonnes * sizeof(int));
        for (int j = 0; j < colonnes; j++) {
            matrice->tab[i][j] = 0;
        }
    }
}


/**
 * @brief Libère la mémoire allouée pour une matrice.
 * @param matrice Pointeur vers la structure matriceTab à libérer
 * @param lignes Nombre de lignes dans la matrice
 */
void libererMatrice(matriceTab *matrice, int lignes) {
    // Libérer le tableau d'entiers
    for (int i = 0; i < lignes; i++) {
        free(matrice->tab[i]);
    }
    free(matrice->tab);
}