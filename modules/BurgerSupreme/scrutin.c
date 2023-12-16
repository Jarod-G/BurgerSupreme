/**
 * @file scrutin.c
 * @author Handwerk Hippolyte
 * @author Jarod Gineste
 * @brief Programme principale qui execute les différentes fonctions de votes
 * @version 0.1
 * @date 2023-12-14
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>
#include <ctype.h>

#include "lecture_csv.h"
#include "condorcet.h"
#include "jugementMajoritaire.h"
#include "uninominal.h"


void afficherBarreDeChargement(int pourcentage) {
    int i;
    const int largeur = 50;
    int nbBarres = pourcentage * largeur / 100;

    printf("[");
    for (i = 0; i < nbBarres; i++) {
        printf("#");
    }
    for (; i < largeur; i++) {
        printf(" ");
    }
    printf("] %d%%\r", pourcentage);
    fflush(stdout);
}


int main(int argc,char* argv[]){
    if(argc < 5){
        printf("Usage : %s -i <fichier_ballot.csv> -d[option] <fichier_ballot.csv> -o[option] <nom_fichier_log> -m <methode_de_vote> [all,uni1,uni2,...]",argv[0]);
        exit(EXIT_FAILURE);
    }
    int option;
    int i_utilise=0;
    int d_utilise=0;
    int o_utilise=0;
    int methode[6];
    
    for (int i=0;i<7;i++){
        methode[i]=0;
    }
    
    char* fichierBallots;
    char* fichierLog;
    
    printf("\nAnalyse du fichier de données (csv) :\n");
    int i;
    for (i = 0; i <= 100; i++) {
        afficherBarreDeChargement(i);
        usleep(15000);  // Simule un travail en attente
    }

    printf("\n\n");

    while ((option = getopt(argc, argv, "i:d:o:m:")) != -1) {
        switch (option) {
            case 'i':
                // Traitement pour l'option -i
                if(d_utilise){
                    printf("on ne peut pas utiliser -i et -d en meme temps");
                    exit(EXIT_FAILURE);
                }
                i_utilise=1;
                fichierBallots=optarg;
                break;
            case 'd':
                // Traitement pour l'option -d
                if(i_utilise){
                    printf("on ne peut pas utiliser -i et -d en meme temps");
                    exit(EXIT_FAILURE);
                }
                d_utilise=1;
                fichierBallots=optarg;
                break;
            case 'o':
                // Traitement pour l'option -o
                fichierLog=optarg;
                o_utilise=1;
                break;

            case 'm':
                //Traitement pour l'option -m
                if (strcmp(optarg, "uni1") == 0) {
                    methode[0] = 1;
                } else if (strcmp(optarg, "uni2") == 0) {
                    methode[1] = 1;
                }else if (strcmp(optarg, "cm") == 0) {
                    methode[2] = 1;
                }else if (strcmp(optarg, "cp") == 0) {
                    methode[3] = 1;
                }else if (strcmp(optarg, "cs") == 0) {
                    methode[4] = 1;
                }else if (strcmp(optarg, "jm") == 0) {
                    methode[5] = 1;
                }else if (strcmp(optarg, "all") == 0) {
                    methode[6] = 1;
                } else {
                    printf("Option non reconnue pour -m : %s\n", optarg);
                    exit(EXIT_FAILURE);
                }
                break;
            case '?':
                // Gestion des options non reconnues ou mal formées
                if (optopt == 'a' || optopt == 'b') {
                    exit(EXIT_FAILURE);
                } else if (isprint(optopt)) {
                    exit(EXIT_FAILURE);
                } else {
                    exit(EXIT_FAILURE);
                }
                break;
            default:
                break;
        }
    }

    if(!o_utilise){
        fichierLog = "log.txt";
    }

    voteElecteur **v_elect = malloc(MAX_VOTES_E * sizeof(voteElecteur));
    nbElecteurs *nb_elect = malloc(sizeof(nbElecteurs));
    lireFichierCSV_vote(fichierBallots, v_elect, nb_elect);

    int NB_DUELS = NB_CANDIDAT - 1;

    int **matricePoids = malloc(NB_CANDIDAT * sizeof(int *));
    int **matriceArcsP = malloc(NB_CANDIDAT * sizeof(int *));
    

    for (int i = 0; i < NB_CANDIDAT; i++) {
        matricePoids[i] = malloc(NB_DUELS * sizeof(int));
        for (int j = 0; j < NB_DUELS; j++) {
            matricePoids[i][j] = 0;
        }
        matriceArcsP[i] = malloc(NB_CANDIDAT * sizeof(int));
        for (int j = 0; j < NB_CANDIDAT; j++) {
            matriceArcsP[i][j] = 0;
        }
        
    }

    
    duelsCalculsArcs(v_elect, nb_elect->nb_electeur, matricePoids);
    duelsCalculsArcsPaires(v_elect, nb_elect->nb_electeur, matriceArcsP);

    /*METTRE LE LOG EMPTY*/
    FILE *fptr = fopen(fichierLog,"w");
    fprintf(fptr,"\n");
    fclose(fptr);

    if(methode[0]){
        uninominal1tour(v_elect,nb_elect->nb_electeur,fichierLog);
    }
    if(methode[1]){
        uninominal2tour(v_elect,nb_elect->nb_electeur,fichierLog);
    }
    if(methode[2]){
        int vainqueur = condorcetMinimax(matricePoids);
        printf("Mode de scrutin : Condorcet minimax , %d candidats, %d votants, vainqueur = %s\n",NB_CANDIDAT,nb_elect->nb_electeur,burgers[vainqueur]);
    }
    if(methode[3]){
        printf("En cours de développement...\n");
        //condorcetPaire(matricePoids);
    }
    if(methode[4]){
        int vainqueur = condorcet(matricePoids);
        if(vainqueur != -1){
            printf("Mode de scrutin : Condorcet , %d candidats, %d votants, vainqueur = %s\n",NB_CANDIDAT,nb_elect->nb_electeur,burgers[vainqueur]);
        }else{
            printf("Il n'existe pas de vainqueur de condorcet avec la méthode de scrutin simple.\n");
        }
        vainqueur = condorcetSchulze(matricePoids);
        if (vainqueur != -1)
        {
            printf("Mode de scrutin : Condorcet Schulze , %d candidats, %d votants, vainqueur = %s\n",NB_CANDIDAT,nb_elect->nb_electeur,burgers[vainqueur]);
        }
        
    }
    if(methode[5]){
        jugementMajoritaire(v_elect,nb_elect->nb_electeur,fichierLog);
    }
    if(methode[6]){
        uninominal1tour(v_elect,nb_elect->nb_electeur,fichierLog);
        uninominal2tour(v_elect,nb_elect->nb_electeur,fichierLog);
        int vainqueur = condorcetSchulze(matricePoids);
        if (vainqueur != -1)
        {
            printf("Mode de scrutin : Condorcet Schulze , %d candidats, %d votants, vainqueur = %s\n",NB_CANDIDAT,nb_elect->nb_electeur,burgers[vainqueur]);
        }

        //condorcetPaire(matricePoids);

        vainqueur = condorcetMinimax(matricePoids);
        printf("Mode de scrutin : Condorcet minimax , %d candidats, %d votants, vainqueur = %s\n",NB_CANDIDAT,nb_elect->nb_electeur,burgers[vainqueur]);
        
        
        
        jugementMajoritaire(v_elect,nb_elect->nb_electeur,fichierLog);
    }
    

    for (int i = 0; i < NB_CANDIDAT; i++) {
        free(matricePoids[i]);
        free(matriceArcsP[i]);
    }

    free(matricePoids);
    free(matriceArcsP);

    free(v_elect);
    free(nb_elect);

    return 0;
}