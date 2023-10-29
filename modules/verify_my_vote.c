/**
 * @file verify_my_vote.c
 * @author Gineste Jarod
 * @author Barcelo Fanny
 * @author Handwerk Hippolyte 
 * @brief Programme permettant de récupèrer les fichiers utiles 
 * @version 0.1
 * @date 2023-10-29
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct_data.h"
#include "sha256/sha256.h"
#include "sha256/sha256_utils.h"
#include "sha256/sha256.c"
#include "sha256/sha256_utils.c"
#include "lecture_csv.c"
#include "lecture_csv.h"
#include <ctype.h>

#define STRLONG 60
int indiceElecteur = 0; // VAR GLOBAL

void calcule_hash(char* nom, char* prenom, char* clef,char* hashRes){
    int i = 0;
    strcat(prenom,clef); // Concatene le prenom et la clef

    // Concatenation du nom avec le reste (" " + prenom + clef)
    while(nom[i] !='\0'){
        i++;
    }
    nom[i] = ' ';
    i++;
    for (int j = 0; prenom[j]!='\0'; j++, i++)
    {
        nom[i] = prenom[j];
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
                indiceElecteur = i;
                votes[x] = v_elect[i]->votes_electeur[x];
            }
            find = 1; // HASH TROUVE
        }
        i++;
    }
}


int main(int argc, char* argv[]) {
    /**
    * Cette fonction effectue une opération.
    *
    * @param arg1 Nom en majuscule de l'electeur
    * @param arg2 Prenom de l'electeur avec la 1ere lettre en majuscule
    * @param arg3 Code secret de l'electeur
    * @param arg4 Fichier de vote csv
    *
    * @return Affiche la ligne de vote correpondant à l'electeur
    */
    if (argc != 5) {
        perror("Usage: verify_my_vote <Nom en majuscule> <Prenom> <ClefSecrete> <FichierDeVote>");
        exit(1);
    }
    voteElecteur *v_elect[MAX_VOTES_E];

    char* nom = argv[1];
    // Verification du nom en majuscule
    for (int i = 0; nom[i] != '\0'; i++)
    {
        if(!isupper(nom[i])){
            perror("Le nom n'est pas en majuscule");
            exit(2);
        }
    }
    

    char* prenom = argv[2];
    // Verification de la 1ere lettre du prenom en majuscule
    if(!isupper(prenom[0])){
        perror("Premiere lettre du prenom n'est pas en majuscule");
        exit(3);
    }

    char* clef = argv[3];
    char* fichierBallots = argv[4];
    int bufferSize = SHA256_BLOCK_SIZE;
    char hashRes[bufferSize*2 + 1]; // contiendra le hash en hexadécimal
    calcule_hash(nom,prenom,clef,hashRes);

    int votes_electeur[10];
    send_my_vote(fichierBallots,v_elect,hashRes,votes_electeur);

    printf("\nVous avez voté le %s les choix suivants :\n |", v_elect[indiceElecteur]->date);
    for (int i = 0; i < 10; i++)
    {
        printf(" %d |", votes_electeur[i]);
    }
    printf("\n\n");

    return 0;
}
