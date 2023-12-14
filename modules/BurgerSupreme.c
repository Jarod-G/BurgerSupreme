#include "lecture_csv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void afficherBarreDeChargement(int pourcentage) {
    int i;
    const int largeur = 50;
    int nbBarres = pourcentage * largeur / 100;

    printf("[");
    for (i = 0; i < nbBarres; i++) {
        printf("#");
    }
    for (; i < largeur; i++) {
        printf(" ");
    }
    printf("] %d%%\r", pourcentage);
    fflush(stdout);
}


int main(int argc, char const *argv[])
{
    printf("\nRecherche d'un gagnant avec les différentes méthodes de condorcet :\n");
    int i;
    for (i = 0; i <= 100; i++) {
        afficherBarreDeChargement(i);
        usleep(20000);  // Simule un travail en attente
    }

    printf("\nGagnant trouvé\n\n");
    return 0;
}
