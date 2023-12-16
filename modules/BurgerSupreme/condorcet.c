/**
 * @file condorcet.c
 * @brief Implémentation des fonctions pour tester différentes méthodes Condorcet.
 * @version 0.1
 * @date 2023-11-25
 * @authors Gineste Jarod
 *          Handwerk Hippolyte
 *          Fanny Barcelo
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
 * @return l'indice du winner s'il y a un gagnant de Condorcet sinon -1.
 */
int condorcet(int **duelsMatrice) {
    int NB_DUELS = NB_CANDIDAT - 1;
    int *wins = malloc(NB_CANDIDAT * sizeof(int));

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
        return -1;
    }
    return winner;
}


/**
 * @brief Fonction de log pour conserver les calculs.
 * @return 0 en cas de succès.
 */
int logCondorcet(int **duelsMatrice,const char* fichierLog){
    int NB_DUELS = NB_CANDIDAT - 1;
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
