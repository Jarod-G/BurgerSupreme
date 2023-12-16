#include "condorcet.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int condorcetMinimax(int **duelsMatrice) {
    int minLocal=duelsMatrice[0][0];
    int meilleurmin=duelsMatrice[0][0];
    int posVainqueur=0;
    for (int candidat = 0; candidat < NB_CANDIDAT; candidat++){
        for (int duel = 0; duel < NB_DUELS; duel++){
            if(minLocal > duelsMatrice[candidat][duel]){
                minLocal = duelsMatrice[candidat][duel];
            }
        }
        if(minLocal < meilleurmin){
            meilleurmin = minLocal;
            posVainqueur = candidat;
        }
    }
    
}