/**
 * @file jugementMajoritaire.c
 * @author Handwerk Hippolyte
 * @author Gineste Jarod
 * @brief this function gives the winner of the Majority judgment
 * @version 0.1
 * @date 2022-12-03
 */

#include "../utils/struct_data.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
const char *nomAppreciation[6] = {"Très Bien" , "Bien" , "Assez Bien" , "Passable", "Insuffisant","À Rejeter"};


float * appreciationCandidat(voteElecteur **votes,int numCandidat,int nbVotants,int nbCandidat){
    /**
    * @brief This function gives the grade and the score
    * @param voteElecteur from struct_data.h
    * @param nbCandidat nombre de candidat à l'election
    * @param nbElecteur nombre d' electeur à l'election
    * @return float* tab (appreciation, score)
    */

    float * tab = malloc(6 * sizeof(float));//on compte les votes en fonction de l'appreciation
    float * appCandidat= malloc(2*sizeof(float));
    float median;
    int appreciation=0;//on va chercher le point median 
    
    for(unsigned i = 0 ; i < nbVotants; i++){
        if (votes[i]->votes_electeur[numCandidat] != -1){
                tab[votes[i]->votes_electeur[numCandidat]] += 1.0;
        }
    }
    
    median=(float)nbVotants/2;

    while (median > 0){
        median -= tab[appreciation++];//on soustrait le score des categories jusqu'a ce que le median soit inferieur a 0
    }
    
    float scoreMedian = tab[appreciation-1];//on le score de la categorie du point median
    
    appCandidat[0] = (float)appreciation;
    appCandidat[1] = scoreMedian;
    free(tab);
    return appCandidat;
}


void jugementMajoritaire(voteElecteur **votes,int nbVotants,int nbCandidat){
    float * candidatGagnant=appreciationCandidat(votes, 0, nbVotants, nbCandidat);
    int burgerGagnant=0;
    float * candidat;
    for(unsigned i=1; i<nbCandidat; i++){
        candidat=appreciationCandidat(votes, i, nbVotants, nbCandidat);
        if ((candidat[0]<candidatGagnant[0])||(candidat[0]==candidatGagnant[0]&&candidat[1]>candidatGagnant[1])){// si le candidat i à une meilleure appreciation ou si elle la meme et un meilleur score il devient le nouveau gagnant potentiel
            candidatGagnant=candidat;
            burgerGagnant=i;
        }
    }
    printf("Le gagnant est %s avec la mention %s (%f) \n",burgers[burgerGagnant],nomAppreciation[(int)candidat[0]],(candidat[1]/nbVotants)*100);
    free(candidat);
}
