#ifndef JUGEMENT_MAJORITAIRE_H
#define JUGEMENT_MAJORITAIRE_H

#include "struct_data.h"
#include <stdio.h>

void jugementMajoritaire(voteElecteur **votes, int nbVotants, const char *fichierLog);
float *appreciationCandidat(voteElecteur **votes,int numCandidat,int nbVotants,FILE *fptr);


#endif