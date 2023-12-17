/**
 * @file condorcet.c
 * @brief Implémentation des fonctions pour tester différentes méthodes Condorcet.
 * @version 0.1
 * @date 2023-12-14
 * @author Gineste Jarod
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
 * @param matriceTab Matrice de votes des électeurs.
 * @param maxElecteurs Nombre maximum d'électeurs.
 * @param duelsMatrice Matrice pour stocker les résultats des duels entre les candidats.
 */
void duelsCalculsArcsMatrice(int **matriceTab, int maxElecteurs, int **duelsMatrice) {
    for (int ligne = 0; ligne < NB_CANDIDAT; ligne++) {
        for (int col = 0; col < NB_CANDIDAT; col++) {
            if (ligne != col) {
                if (matriceTab[ligne][col] > matriceTab[col][ligne]) {
                    duelsMatrice[ligne][col] = matriceTab[ligne][col] - matriceTab[col][ligne];
                }
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
int condorcet(int **duelsMatrice,const char* fichierLog) {
    FILE *fptr;
    fptr = fopen(fichierLog, "a");
    fprintf(fptr,"\nRESULTAT CONDORCET\n");
    if (fptr == NULL) {
        printf("Impossible d'ouvrir le fichier.");
        return 1;
    }

    int NB_DUELS = NB_CANDIDAT - 1;
    int *wins = malloc(NB_CANDIDAT * sizeof(int));


    // Calculer le nombre total de duels remportés par chaque candidat
    for (int i = 0; i < NB_CANDIDAT; i++) {
        wins[i] = 0;
        for (int j = 0; j < NB_DUELS; j++) {
            if (duelsMatrice[i][j] > 0) {
                wins[i] += 1;
            }
        }
        
    }
    
    // FICHIER LOG
    for(int i=0;i<NB_CANDIDAT;i++){
        fprintf(fptr,"%s à remporté %d duels\n",burgers[i],wins[i]);
    }

    // Trouver le candidat avec le plus grand nombre de duels remportés
    int winner = -1;
    for (int i = 0; i < NB_CANDIDAT; i++) {
        if (wins[i] == NB_DUELS) {
            winner = i;
        }
    }
    if (winner == -1) {
        return -1;
    }
    
    fclose(fptr);
    return winner;
}