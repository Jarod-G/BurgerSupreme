/**
 * @file lecture_csv.c
 * @author Gineste Jarod
 * @brief Fonctions de lecture de fichiers CSV pour extraire et structurer les données
 * @version 0.1
 * @date 2023-10-28
 */

#include "lecture_csv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 * @brief Lit un fichier CSV de votes et stocke les données dans une structure voteElecteur.
 * @param nomFichier Chemin du fichier CSV des votes
 * @param v_elect Tableau de structures voteElecteur pour stocker les données
 * @param nb_elect Structure pour stocker le nombre total d'électeurs
 */
void lireFichierCSV_vote(const char *nomFichier, voteElecteur **v_elect,nbElecteurs* nb_elect) {
    FILE *fichier;
    int ligne_count = 0;
    char buffer[512];

    if ((fichier = fopen(nomFichier, "r")) == NULL) {
        perror("Erreur d'ouverture du fichier");
        exit(1);
    }

    // Ignore la première ligne
    if (fgets(buffer, sizeof(buffer), fichier) == NULL) {
        fprintf(stderr, "Fichier vide.\n");
        fclose(fichier);
        exit(1);
    }
    
    // Lecture des lignes
    int col_count;
    while (fgets(buffer, sizeof(buffer), fichier)) {
        char *token = strtok(buffer, ",");
        col_count = 0;
        v_elect[ligne_count] = malloc(sizeof(voteElecteur)); // Allouer de la mémoire pour v_elect[ligne_count]
        char *newline = strchr(token, '\n');
        while (token != NULL && newline==NULL) {
            switch (col_count) {
                case 0:
                    v_elect[ligne_count]->reponse = atoi(token);
                    break;
                case 1:
                    v_elect[ligne_count]->date = strdup(token);
                    break;
                case 2:
                    v_elect[ligne_count]->cours = strdup(token);

                    break;
                case 3:
                    v_elect[ligne_count]->hash = strdup(token);
                    break;
                default:
                    v_elect[ligne_count]->votes_electeur[col_count-4] = atoi(token);
                    break;
            }
            token = strtok(NULL, ",");
            col_count++;
        }
        ligne_count++;
    }
    NB_CANDIDAT = col_count - 4;
    nb_elect->nb_electeur = ligne_count;
    fclose(fichier);
}


/**
 * @brief Lit un fichier CSV de matrice de votes et stocke les données dans une structure matriceTab.
 * @param nomFichier Chemin du fichier CSV de la matrice de votes
 * @param matrice Structure matriceTab pour stocker les données
 */
void lireMatriceCSV(const char *nomFichier, matriceTab *matrice) {
    FILE *fichier;
    int ligne_count = 0;
    int col_count = 0;
    char buffer[256];
    
    if ((fichier = fopen(nomFichier, "r")) == NULL) {
        perror("Erreur d'ouverture du fichier");
        exit(1);
    }

    // Ignore la première ligne
    if (fgets(buffer, sizeof(buffer), fichier) == NULL) {
        fprintf(stderr, "Fichier vide.\n");
        fclose(fichier);
        exit(1);
    }
    
    // Lecture des lignes
    while (fgets(buffer, sizeof(buffer), fichier)) {
        char *token = strtok(buffer, ",");
        col_count = 0;
        char *newline = strchr(token, '\n');
        while (token != NULL && newline==NULL) {
            matrice->tab[ligne_count][col_count] = atoi(token);
            token = strtok(NULL, ",");
            col_count++;
        }
        ligne_count++;
    }
    matrice->nbElecteurs = ligne_count;
    matrice->nbCandidat = col_count;
    NB_CANDIDAT = col_count;
    fclose(fichier);
}

/**
 * @brief Lit un fichier CSV d'électeurs et stocke les données dans une structure electeur.
 * @param nomFichier Chemin du fichier CSV des électeurs
 * @param electeurs Tableau de structures electeur pour stocker les données
 * @param nb_elect Structure pour stocker le nombre total d'électeurs
 */
void lireFichierCSV_electeur(const char* nomFichier, electeur **electeurs,nbElecteurs* nb_elect) {
    FILE *fichier;
    int ligne_count = 0;
    char buffer[512];

    if ((fichier = fopen(nomFichier, "r")) == NULL) {
        perror("Erreur d'ouverture du fichier");
        exit(1);
    }

    // Ignore la première ligne
    if (fgets(buffer, sizeof(buffer), fichier) == NULL) {
        fprintf(stderr, "Fichier vide.\n");
        fclose(fichier);
        exit(1);
    }
    
    // Lecture des lignes
    while (fgets(buffer, sizeof(buffer), fichier)) {
        char *token = strtok(buffer, " ");
        int col_count = 0;
        electeurs[ligne_count] = malloc(sizeof(electeur)); // Allouer de la mémoire pour v_elect[ligne_count]
        while (token != NULL && col_count < 2) {
            switch (col_count) {
                case 0:
                    electeurs[ligne_count]->num_electeur = atoi(token);
                    break;
                case 1:
                    electeurs[ligne_count]->clef = strdup(token);
                    break;
                default:
                    break;
            }
            token = strtok(NULL, " ");
            col_count++;
        }
        ligne_count++;
    }
    nb_elect->nb_electeur = ligne_count;
    fclose(fichier);
}
