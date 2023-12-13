/**
 * @file condorcet_paires.c
 * @author Barcelo Fanny
 * @brief this file gives functions to find the winner of the Condorcet Paires election
 * @version 0.1
 * @date 2023-12/08
 */


#include "../utils/struct_data.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void condorcetPaires(int **duelsMatrice) {
	int matriceArc[NB_CANDIDAT][NB_CANDIDAT];
	
	// Initialiser la matrice à 0
	for (int i = 0; i < NB_CANDIDAT; i++) {
        	for (int j = 0; j < NB_CANDIDAT; j++) {
            	matriceArc[i][j] = 0;
        	}
   	 }
	
	// Calculer la matrice des arcs 
	
	for (int i = 0; i < NB_CANDIDAT; i++) {
        	for (int j = 0; j < NB_CANDIDAT-1; j++) {
        		int arc = duelsMatrice[i][j][0]-duelsMatrice[i][j][1];
        		// enlever également les arcs qui créé une boucle//
        		if (arc > 0){
        			matriceArc[i],[j]= arc;
        	 }
        }
        
        //Trouver le gagnant//
        int candidats[nombreCandidat];
        for (int i=0; i <NB_CANDIDAT; i++){
        	candidats[i] = 0;
        }
        for(int i=0; i<NB_CANDIDAT -1; i++) {
        	for (int j = 0; j < NB_CANDIDAT; j++) {
        		if (matriceArc[j][i] > 0){
        			if(j>=i){
        				candidats[i+1] = 1;
        			}
        			else {
        				candidats[i] = 1;
        			}
        		}
        	}
        }
        int gagnant = 0;
        for (int i=0; i <NB_CANDIDAT; i++){
        	if (candidat[i] =  0){
        		gagnant = i;
        		break;
        	}
        }
}
         
        		    	
