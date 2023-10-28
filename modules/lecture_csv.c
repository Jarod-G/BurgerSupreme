#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct_data.h"
#include "lecture_csv.h"


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
    fclose(fichier);
}


void lireFichierCSV(const char* fichierVotesElecteurs,voteElecteur *v_elect[MAX_VOTES_E]){
    // INITIALISATION DES STRUCTURES
    lireFichierCSV_vote(fichierVotesElecteurs, v_elect);
}

/*
int main(){
    voteElecteur *v_elect[MAX_VOTES_E];
    lireFichierCSV("../data/VoteCondorcet.csv",v_elect);

    for (int i = 0; i < MAX_VOTES_E-1; i++)
    {
        for (int x = 0; x < 10; x++)
        {
            printf("%d,\n",v_elect[i]->votes_electeur[x]);
        }
        
    }
    
}
*/