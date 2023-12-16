/**
 * @file condorcet.c
 * @author Gineste Jarod
 * @brief Ce fichier est le fichier principal pour tester différentes fonctions de méthodes Condorcet.
 * @version 0.1
 * @date 2023-11-25
 */

#include "condorcet.h"
#include "lecture_csv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


/**
 * @brief Calcule les résultats des duels entre les candidats.
 * @param v_elect Tableau de structures voteElecteur représentant les votes de chaque électeur.
 * @param maxElecteurs Nombre maximum d'électeurs.
 * @param duelsMatrice Matrice pour stocker les résultats des duels entre les candidats.
 */
void duelsCalculsArcs(voteElecteur *v_elect[], int maxElecteurs, int **duelsMatrice) {
    for (int candidat = 0; candidat < NB_CANDIDAT; candidat++) {
        int i_currentCandidat = 0;
        for (int currentCandidat = 0; currentCandidat < NB_CANDIDAT; currentCandidat++) {
            if (currentCandidat != candidat) {
                int nbWin = 0;
                int nbLoose = 0;
                for (int electeur = 0; electeur < maxElecteurs; electeur++) {
                    if (currentCandidat != candidat && v_elect[electeur]->votes_electeur[candidat] != v_elect[electeur]->votes_electeur[currentCandidat]) {
                        if (v_elect[electeur]->votes_electeur[candidat] != -1) {
                            if (v_elect[electeur]->votes_electeur[candidat] < v_elect[electeur]->votes_electeur[currentCandidat] || v_elect[electeur]->votes_electeur[currentCandidat] == -1) {
                                nbWin++;
                            } else {
                                nbLoose++;
                            }
                        } else {
                            nbLoose++;
                        }
                    }
                }
                if (nbWin > nbLoose) {
                    duelsMatrice[candidat][i_currentCandidat] = nbWin - nbLoose;
                }
                i_currentCandidat++;
            }
        }
    }
}


/**
 * @brief Calcule les résultats des duels entre les candidats.
 * @param v_elect Tableau de structures voteElecteur représentant les votes de chaque électeur.
 * @param maxElecteurs Nombre maximum d'électeurs.
 * @param duelsMatrice Matrice pour stocker les résultats des duels entre les candidats.
 */
void duelsCalculsArcsPaires(voteElecteur *v_elect[], int maxElecteurs, int **duelsMatrice) {
    for (int candidat = 0; candidat < NB_CANDIDAT; candidat++) {
        for (int currentCandidat = 0; currentCandidat < NB_CANDIDAT; currentCandidat++) {
            if (currentCandidat != candidat) {
                int nbWin = 0;
                int nbLoose = 0;
                for (int electeur = 0; electeur < maxElecteurs; electeur++) {
                    if (currentCandidat != candidat && v_elect[electeur]->votes_electeur[candidat] != v_elect[electeur]->votes_electeur[currentCandidat]) {
                        if (v_elect[electeur]->votes_electeur[candidat] != -1) {
                            if (v_elect[electeur]->votes_electeur[candidat] < v_elect[electeur]->votes_electeur[currentCandidat] || v_elect[electeur]->votes_electeur[currentCandidat] == -1) {
                                nbWin++;
                            } else {
                                nbLoose++;
                            }
                        } else {
                            nbLoose++;
                        }
                    }
                }
                if (nbWin > nbLoose) {
                    duelsMatrice[candidat][currentCandidat] = nbWin - nbLoose;
                }
            }
        }
    }
}


/**
 * @brief Applique la méthode Condorcet pour déterminer le gagnant du vote.
 * @param duelsMatrice Matrice des résultats des duels entre les candidats.
 * @return 1 si il a un gagnant de condorcet sinon 0.
 */
int condorcet(int duelsMatrice[5][5]) {
    int wins[NB_CANDIDAT] = {0};

    // Calculer le nombre total de duels remportés par chaque candidat
    for (int i = 0; i < NB_CANDIDAT; i++) {
        for (int j = 0; j < NB_DUELS; j++) {
            if (duelsMatrice[i][j] > 0) {
                wins[i] += 1;
            }
        }
    }

    // Trouver le candidat avec le plus grand nombre de duels remportés
    int winner = -1;
    for (int i = 0; i < NB_CANDIDAT; i++) {
        if (wins[i] == 9) {
            winner = i;
        }
    }
    if (winner == -1) {
        return 0;
    }
    return 1;
}


/**
 * @brief Fonction de log pour conserver les calculs.
 * @return 0 en cas de succès.
 */
int logCondorcet(int **duelsMatrice,const char* fichierLog){
    FILE *fptr;
    fptr = fopen(fichierLog, "a");

    if (fptr == NULL) {
        printf("Impossible d'ouvrir le fichier.");
        return 1;
    }
    fprintf(fptr,"\t|");
    // Écriture des libellés de colonnes dans le fichier
    for(int i=0;i<NB_CANDIDAT;i++){
 
        fprintf(fptr,"%s |\t",burgers[i]);
    }
    fprintf(fptr,"\n");
    fprintf(fptr, "-------------\n");

    // Écriture des données dans le fichier
    for (int i = 0; i < NB_CANDIDAT; i++) {
        fprintf(fptr, "%s \t\t\t|", burgers[i]);
        for (int j = 0; j <= NB_DUELS; j++) {
            if(i!=j){
            fprintf(fptr, "%d |\t", duelsMatrice[i][j]);
            }
            else{
                fprintf(fptr,"X |\t");
            }
        }
        fprintf(fptr, "\n");
    }
    return 0;
}


/**
 * @brief Fonction principale pour tester les différentes méthodes Condorcet.
 * @return 0 en cas de succès.
 */
int main() {
    /*
    voteElecteur **v_elect = malloc(MAX_VOTES_E * sizeof(voteElecteur));
    nbElecteurs *nb_elect = malloc(sizeof(nbElecteurs));

    char* fichierBallots = "/home/jarod/Documents/projet/BurgerSupreme/data/VoteCondorcet.csv";

    lireFichierCSV_vote(fichierBallots, v_elect, nb_elect);

    // Allouez de la mémoire pour la matrice dynamique
    int **matricePoids = malloc(NB_CANDIDAT * sizeof(int *));
    int **matriceArcsP = malloc(NB_CANDIDAT * sizeof(int *));
    

    for (int i = 0; i < NB_CANDIDAT; i++) {
        matricePoids[i] = malloc(NB_DUELS * sizeof(int));
        for (int j = 0; j < NB_DUELS; j++) {
            matricePoids[i][j] = 0;
        }
        matriceArcsP[i] = malloc(NB_CANDIDAT * sizeof(int));
        for (int j = 0; j < NB_CANDIDAT; j++) {
            matriceArcsP[i][j] = 0;
        }
        
    }

    duelsCalculsArcs(v_elect, nb_elect->nb_electeur, matricePoids);
    duelsCalculsArcsPaires(v_elect, nb_elect->nb_electeur, matriceArcsP);
    
    
    //condorcetSchulzeSchwartz(matricePoids);
    
    
    for (int i = 0; i < NB_CANDIDAT; i++) {
        free(matricePoids[i]);
        free(matriceArcsP[i]);
    }

    free(matricePoids);
    free(matriceArcsP);

    free(v_elect);
    free(nb_elect);
    */
    
    int matrice[5][5] = 
    {   {0,0,7,15,0},
        {5,0,0,21,0},
        {0,13,0,0,3},
        {0,0,11,0,0},
        {1,9,0,17,0}
    };

    //condorcetPaires(matrice);
    if(condorcet(matrice) == 1){
        printf("vainq condorcet !\n");
    }else{
        printf("Pas de gagnat !\n");
    }
    
    int grapheDuels[NB_CANDIDAT][NB_CANDIDAT];

    creerGrapheDuels(matrice, grapheDuels);

    int gagnant = trouverGagnantCondorcetPaires(grapheDuels);

    printf("Le gagnant selon la méthode Condorcet par paires est le candidat %d\n", gagnant);


    return 0;
}