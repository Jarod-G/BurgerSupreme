// Exemple de condorcet_utils.h
#ifndef CONDORCET_H
#define CONDORCET_H

#include "struct_data.h"

void duelsCalculsArcs(voteElecteur *v_elect[], int maxElecteurs, int **duelsMatrice);
void condorcet(int **duelsMatrice);

void condorcetSchulze(int **duelsMatrice);
void condorcetSchulzeSchwartz(int **duelsMatrice);
void ensembleSchwartz(int **duelsMatrice, int schwartzSet[NB_CANDIDAT]) ;

//void condorcetPaires(int **duelsMatrice);


#endif
