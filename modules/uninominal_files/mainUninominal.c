#include "../utils/lecture_csv.h"
#include "../utils/struct_data.h"
#include "uninominal.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s <1/2 tours> <FichierDeVote>",argv[0]);
        exit(1);
    }
    voteElecteur *v_elect[MAX_VOTES_E];
    nbElecteurs nb_elect;

    int typeUninominal = atoi(argv[1]);
    char* fichierBallots = argv[2];

    lireFichierCSV_vote(fichierBallots,v_elect,&nb_elect);

    if(typeUninominal == 1){
        uninominal1tour(v_elect,NB_CANDIDAT,nb_elect.nb_electeur);
    }else if(typeUninominal == 2){
        uninominal2tour(v_elect,NB_CANDIDAT,nb_elect.nb_electeur);

    }else{
        printf("Vote uninominal < 1 tour ou > 2 tours impossible.\n");
    }
    return 0;
}