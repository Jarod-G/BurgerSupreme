// Exemple de condorcet_utils.h
#ifndef CONDORCET_H
#define CONDORCET_H

#include "struct_data.h"

void duelsCalculsArcs(voteElecteur *v_elect[], int maxElecteurs, int **duelsMatrice);
int condorcet(int duelsMatrice[5][5]);

void condorcetSchulze(int **duelsMatrice);
void ensembleSchwartz(int **duelsMatrice, int schwartzSet[NB_CANDIDAT]);
/*void supprimerPoid(int matricePoids[NB_CANDIDAT][NB_CANDIDAT]);

void condorcetPaires(int matrice[5][5]);*/
//int* identifierCycle(int matriceArc[5][5],int candidat);
void condorcetMinimax(int **duelsMatrice);
int trouverGagnantCondorcetPaires(int grapheDuels[NB_CANDIDAT][NB_CANDIDAT]);
void creerGrapheDuels(int scores[NB_CANDIDAT][NB_CANDIDAT], int grapheDuels[NB_CANDIDAT][NB_CANDIDAT]);

#endif
