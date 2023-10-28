#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct_data.h"
#include "sha256.h"
#include "sha256_utils.h"
#include "sha256.c"
#include "sha256_utils.c"
#include "lecture_csv.c"
#include "lecture_csv.h"
#define STRLONG 60


void calcule_hash(char* nom, char* clef,char* hashRes){
    int i = 0;
    while(nom[i] !='\0'){
        i++;
    }
    nom[i] = ' ';
    i++;
    for (int j = 0; clef[j]!='\0'; j++, i++)
    {
        nom[i] = clef[j];
    }
    sha256ofString((BYTE *)nom,hashRes); // hashRes contient maintenant le hash de l'item
}


void send_my_vote(char* fichierBallots,voteElecteur* v_elect[MAX_VOTES_E], char* hashRes, int* votes){
    lireFichierCSV_vote(fichierBallots,v_elect);
    int find = 0;
    int i = 0;
    while(!find || i == MAX_VOTES_E - 1)
    {
        if(strcmp(v_elect[i]->hash, hashRes) == 0){
            for (int x = 0; x < 10; x++)
            {
                votes[x] = v_elect[i]->votes_electeur[x];
            }
            find = 1; // HASH TROUVE
        }
        i++;
    }
}


int main(int argc, char* argv[]) {
    if (argc != 4) {
        perror("Usage: verify_my_vote <NomComplet> <ClefSecrete> <FichierDeVote>");
        return 1;
    }
    voteElecteur *v_elect[MAX_VOTES_E];

    char* nomComplet = argv[1];
    char* clef = argv[2];
    char* fichierBallots = argv[3];
    int bufferSize = SHA256_BLOCK_SIZE;
    char hashRes[bufferSize*2 + 1]; // contiendra le hash en hexadécimal
    calcule_hash(nomComplet,clef,hashRes);

    int votes_electeur[10];
    send_my_vote(fichierBallots,v_elect,hashRes,votes_electeur);
    
    printf("Vous avez voté les choix suivants :\n");
    for (int i = 0; i < 10; i++)
    {
        printf("Vote %d - %d\n", i+1, votes_electeur[i]);
    }
    printf("\n");

    return 0;
}
