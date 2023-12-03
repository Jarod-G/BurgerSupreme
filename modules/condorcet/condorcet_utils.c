/**
 * @file condorcet_utils.c
 * @author Gineste Jarod
 * @brief this utils give functions to make different version of condorcet methode
 * @version 0.1
 * @date 2023-11-22
 */

#include "../utils/struct_data.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void duelsCalculs (voteElecteur *v_elect[], int maxElecteurs, int **duelsMatrice){
    
    for (int candidat = 0; candidat < NB_CANDIDAT; candidat++)
    {
        int i_currentCandidat = 0;
        for( int currentCandidat = 0; currentCandidat < NB_CANDIDAT; currentCandidat++)
        {
            if(currentCandidat != candidat ){
                int nbWin = 0;
                int nbLoose = 0;
                for (int electeur = 0; electeur < maxElecteurs; electeur++)
                {
                    if(currentCandidat != candidat){
                        if(v_elect[electeur]->votes_electeur[candidat] != v_elect[electeur]->votes_electeur[currentCandidat]){
                            if(v_elect[electeur]->votes_electeur[candidat] != -1){
                                if(v_elect[electeur]->votes_electeur[candidat] < v_elect[electeur]->votes_electeur[currentCandidat] || v_elect[electeur]->votes_electeur[currentCandidat] == -1){
                                    nbWin++;
                                }else{
                                    nbLoose++;
                                }
                            }else{
                                nbLoose++;
                            }
                        }
                    }       
                }
                if(nbWin > nbLoose){
                    duelsMatrice[candidat][i_currentCandidat] = nbWin - nbLoose;
                    
                }
                i_currentCandidat++;
            }
        }
    }
}


void condorcet(int **duelsMatrice) {
    int wins[NB_CANDIDAT] = {0};

    // Calculer le nombre total de duels remportés par chaque candidat
    for (int i = 0; i < NB_CANDIDAT; i++) {
        for (int j = 0; j < NB_DUELS; j++) {
            if(duelsMatrice[i][j] > 0){
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
    if(winner == -1){
        printf("Il n'y a pas de gagnant de Condorcet\n");
    }else{
        printf("Le gagnant du vote Condorcet est %s\n", burgers[winner]);
    }
    
}