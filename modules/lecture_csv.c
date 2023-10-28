#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct_data.h"

int MAX_LIGNE_E = 100;
int MAX_COL_E = 2;
int MAX_VOTES_E = 50;
int nb_votants = 0;

void lireFichierCSV_vote(const char *nomFichier, voteElecteur *v_elect[MAX_VOTES_E]) {
    FILE *fichier;
    int ligne_count = 0;
    char buffer[1000];

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
        int col_count = 0;
        v_elect[ligne_count] = malloc(sizeof(voteElecteur)); // Allouer de la mémoire pour v_elect[ligne_count]
        while (token != NULL && col_count < 14) {
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
    nb_votants = ligne_count;
    fclose(fichier);

}




void lireFichierCSV_electeur(const char* nomFichier, electeur *electeurs[MAX_VOTES_E]) {
    FILE *fichier;
    int ligne_count = 0;
    char buffer[1000];

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
    nb_votants = ligne_count;
    fclose(fichier);
}

void lireFichierCSV(char* fichierElecteur, char* fichierVotesElecteurs){

    // INITIALISATION DES STRUCTURES
    voteElecteur *v_elect[MAX_VOTES_E];
    lireFichierCSV_vote(fichierVotesElecteurs, v_elect);
    electeur *elect[MAX_VOTES_E];
    lireFichierCSV_electeur(fichierElecteur, elect);


    // ELECTEUR AFFICHAGE TEST
    
    for (int i = 0; i < nb_votants - 1 ; i++) {
        printf("Ligne : %d , Numéro de l'électeur : %d, Clef : %s à voté le %s, cours : %s, hash : %s, les réponses suivantes : \n",i+1 ,elect[i]->num_electeur, elect[i]->clef,v_elect[i]->date,v_elect[i]->cours,v_elect[i]->hash);
        for (int x = 0; x < 10; x++)
        {
            printf("Vote %d : %d\n", x ,v_elect[i]->votes_electeur[x]);
        }
    }
    
    
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        perror("Utilisation : lecture_csv <fichierE.csv> <fichierV.csv>");
        return 1;
    }

    lireFichierCSV(argv[1], argv[2]);

    return 0;
}
