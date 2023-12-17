/**
 * @file scrutin.c
 * @authors Handwerk Hippolyte, Jarod Gineste
 * @brief Programme principal qui exécute différentes fonctions de vote
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

// Fonction pour afficher une barre de chargement
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

int main(int argc, char* argv[]) {
    /*
     * VÉRIFICATION DES ARGUMENTS EN LIGNE DE COMMANDE
     *
     * Cette section vérifie le nombre d'arguments passés en ligne de commande
     * et affiche un message d'erreur en cas d'arguments insuffisants.
     */

    if (argc < 5) {
        printf("Usage : %s -i <fichier_ballot.csv> -d[option] <fichier_ballot.csv> -o[option] <nom_fichier_log> -m <methode_de_vote> [all,uni1,uni2,...]", argv[0]);
        exit(EXIT_FAILURE);
    }

    /*
     * INITIALISATION DES VARIABLES
     *
     * Cette section initialise les variables nécessaires pour le traitement
     * des options de ligne de commande et d'autres paramètres du programme.
     */
    int option;
    int i_utilise = 0;
    int d_utilise = 0;
    int o_utilise = 0;
    int methode[7];

    for (int i = 0; i < 7; i++) {
        methode[i] = -1;
    }

    char* fichierBallots;
    char* fichierLog;

    /*
     * ANALYSE DES OPTIONS EN LIGNE DE COMMANDE
     *
     * Cette section analyse les options passées en ligne de commande à l'aide
     * de la fonction getopt pour déterminer le comportement du programme.
     */
    while ((option = getopt(argc, argv, "i:d:o:m:")) != -1) {
        switch (option) {
            case 'i':
                // Option -i : Traitement
                if (d_utilise) {
                    printf("Usage de -i et -d en même temps impossible.\n");
                    exit(EXIT_FAILURE);
                }
                i_utilise = 1;
                fichierBallots = optarg;
                break;
            case 'd':
                // Option -d : Traitement
                if (i_utilise) {
                    printf("Usage de -i et -d en même temps impossible.\n");
                    exit(EXIT_FAILURE);
                }
                d_utilise = 1;
                fichierBallots = optarg;
                break;
            case 'o':
                // Option -o : Traitement
                fichierLog = optarg;
                o_utilise = 1;
                break;
            case 'm':
                // Option -m : Traitement
                if (strcmp(optarg, "uni1") == 0) {
                    methode[0] = 1;
                } else if (strcmp(optarg, "uni2") == 0) {
                    methode[1] = 1;
                } else if (strcmp(optarg, "cm") == 0) {
                    methode[2] = 1;
                } else if (strcmp(optarg, "cp") == 0) {
                    methode[3] = 1;
                } else if (strcmp(optarg, "cs") == 0) {
                    methode[4] = 1;
                } else if (strcmp(optarg, "jm") == 0) {
                    methode[5] = 1;
                } else if (strcmp(optarg, "all") == 0) {
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

    // Si l'option -o n'est pas utilisée, utiliser le fichier log par défaut
    if (!o_utilise) {
        fichierLog = "log.txt";
    }


    /*
     * AFFICHAGE DE LA BARRE DE CHARGEMENT SIMULÉE
     *
     * Simule une barre de chargement pendant la lecture des données CSV.
     */
    printf("\nAnalyse du fichier de données (csv) :\n");

    for (int i = 0; i <= 100; i++) {
        afficherBarreDeChargement(i);
        usleep(10000);  // Simule un travail en attente
    }
    printf("\n\n");


    /*
     * ALLOCATION DE MÉMOIRE POUR LES STRUCTURES DE DONNÉES
     *
     * Cette section alloue de la mémoire pour les différentes structures de données
     * nécessaires au programme, comme les votes des électeurs et les matrices.
     */
    voteElecteur** v_elect = malloc(MAX_VOTES_E * sizeof(voteElecteur));
    nbElecteurs* nb_elect = malloc(sizeof(nbElecteurs));
    matriceTab* matrice = malloc(sizeof(matriceTab));
    int NB_VOTANTS = 0;
    int NB_DUELS = 0;


    /*
     * INITIALISATION DE LA MATRICE POUR -d OU LECTURE DU FICHIER CSV POUR -i
     *
     * Selon l'option utilisée, initialise la matrice à partir du fichier CSV
     * ou lit les votes des électeurs depuis le fichier CSV.
     */
    initialiserMatrice(matrice, MAX_VOTES_E, MAX_CANDIDATS);
    if (d_utilise) {
        lireMatriceCSV(fichierBallots, matrice);
        NB_VOTANTS = matrice->nbElecteurs;
        NB_DUELS = NB_CANDIDAT;
    } else {  // CAS -i PRÉSENT
        lireFichierCSV_vote(fichierBallots, v_elect, nb_elect);
        NB_VOTANTS = nb_elect->nb_electeur;
        NB_DUELS = NB_CANDIDAT - 1;
    }


    /*
     * ALLOCATION DE MÉMOIRE POUR LA MATRICE DE POIDS
     *
     * Cette section alloue de la mémoire pour la matrice de poids utilisée dans les
     * calculs des duels et des poids d'arcs pour différentes méthodes de vote.
     */
    int** matricePoids = malloc(NB_CANDIDAT * sizeof(int*));

    /*
     * CALCUL DES DUELS ET DES POIDS D'ARCS EN FONCTION DES OPTIONS -i OU -d
     *
     * Selon l'option utilisée, calcule les duels et les poids d'arcs nécessaires aux
     * différentes méthodes de vote.
     */
    if (d_utilise) {
        // CAS -d : Allocation de mémoire et calcul des duels et des poids d'arcs
        for (int i = 0; i < NB_CANDIDAT; i++) {
            matricePoids[i] = malloc(NB_CANDIDAT * sizeof(int));
            for (int j = 0; j < NB_CANDIDAT; j++) {
                matricePoids[i][j] = 0;
            }
        }
        duelsCalculsArcsMatrice(matrice->tab, NB_VOTANTS, matricePoids);
    } else {
        // CAS -i : Allocation de mémoire et calcul des duels et des poids d'arcs
        for (int i = 0; i < NB_CANDIDAT; i++) {
            matricePoids[i] = malloc(NB_DUELS * sizeof(int));
            for (int j = 0; j < NB_DUELS; j++) {
                matricePoids[i][j] = 0;
            }
        }
        duelsCalculsArcs(v_elect, NB_VOTANTS, matricePoids);
    }
    
    /*
     * OUVERTURE DU FICHIER LOG EN MODE ÉCRITURE
     *
     * Ouvre le fichier log en mode écriture pour enregistrer les résultats.
     */
    FILE* fptr = fopen(fichierLog, "w");
    fprintf(fptr, "\n");
    fclose(fptr);

    
    /*
        * APPLICATION DES MÉTHODES DE VOTE SÉLECTIONNÉES
        *
        * En fonction des options -m, applique les différentes méthodes de vote
        * pour déterminer les vainqueurs ou les résultats des élections.
    */

    // Méthode de vote : Uninominal 1 tour
    if (methode[0] != -1 && !d_utilise) {
        uninominal1tour(v_elect, NB_VOTANTS, fichierLog);
    }

    // Méthode de vote : Uninominal 2 tours
    if (methode[1] != -1 && ! d_utilise) {
        uninominal2tour(v_elect, NB_VOTANTS, fichierLog);
    }

    // Méthode de vote : Condorcet avec Minimax
    if (methode[2] != -1) {
        int vainqueur = condorcet(matricePoids, fichierLog);
        if (vainqueur != -1) {
            printf("Mode de scrutin : Condorcet , %d candidats, %d votants, vainqueur = %s\n", NB_CANDIDAT, NB_VOTANTS, burgers[vainqueur]);
        } else {
            printf("Il n'existe pas de vainqueur de condorcet avec la méthode de scrutin simple.\n");
        }
        vainqueur = condorcetMinimax(matricePoids, fichierLog, NB_DUELS);
        printf("Mode de scrutin : Condorcet minimax , %d candidats, %d votants, vainqueur = %s\n", NB_CANDIDAT, NB_VOTANTS, burgers[vainqueur]);
    }

    // Méthode de vote : Condorcet Paires(en cours de développement)
    if (methode[3] != -1) {
        printf("En cours de développement...\n");
        // condorcetPaire(matricePoids);
    }

    // Méthode de vote : Condorcet avec Schulze
    if (methode[4] != -1) {
        int vainqueur = condorcet(matricePoids, fichierLog);
        if (vainqueur != -1) {
            printf("Mode de scrutin : Condorcet , %d candidats, %d votants, vainqueur = %s\n", NB_CANDIDAT, NB_VOTANTS, burgers[vainqueur]);
        } else {
            printf("Il n'existe pas de vainqueur de condorcet avec la méthode de scrutin simple.\n");
        }
        vainqueur = condorcetSchulze(matricePoids, fichierLog, NB_DUELS);
        if (vainqueur != -1) {
            printf("Mode de scrutin : Condorcet Schulze , %d candidats, %d votants, vainqueur = %s\n", NB_CANDIDAT, NB_VOTANTS, burgers[vainqueur]);
        }
    }

    // Méthode de vote : Jugement Majoritaire
    if (methode[5] != -1 && !d_utilise) {
        jugementMajoritaire(v_elect, NB_VOTANTS, fichierLog);
    }

    // Méthode de vote : Application de toutes les méthodes si -m all (non applicable si -d est utilisé)
    if (methode[6] != -1 && !d_utilise) {
        uninominal1tour(v_elect, NB_VOTANTS, fichierLog);
        uninominal2tour(v_elect, NB_VOTANTS, fichierLog);

        // CONDORCET SCHULZE
        int vainqueur = condorcetSchulze(matricePoids, fichierLog, NB_DUELS);
        if (vainqueur != -1) {
            printf("Mode de scrutin : Condorcet Schulze , %d candidats, %d votants, vainqueur = %s\n", NB_CANDIDAT, NB_VOTANTS, burgers[vainqueur]);
        }

        // MINIMAX SI IL N'EXISTE PAS DE VAINQUEUR DE CONDORCET
        vainqueur = condorcet(matricePoids, fichierLog);
        if(vainqueur == -1){
            vainqueur = condorcetMinimax(matricePoids, fichierLog, NB_DUELS);
            printf("Mode de scrutin : Condorcet minimax , %d candidats, %d votants, vainqueur = %s\n", NB_CANDIDAT, NB_VOTANTS, burgers[vainqueur]);

        }else{
            printf("Mode de scrutin : Condorcet minimax , %d candidats, %d votants, vainqueur = %s\n", NB_CANDIDAT, NB_VOTANTS, burgers[vainqueur]);
        }

        // condorcetPaire(matricePoids);
        
        jugementMajoritaire(v_elect, NB_VOTANTS, fichierLog);
    }

    // Méthode de vote : Application de toutes les méthodes si -m all (applicable si -d est utilisé)
    if (methode[6] != -1 && d_utilise) {
        int vainqueur = condorcetSchulze(matricePoids, fichierLog, NB_DUELS);
        if (vainqueur != -1) {
            printf("Mode de scrutin : Condorcet Schulze , %d candidats, %d votants, vainqueur = %s\n", NB_CANDIDAT, NB_VOTANTS, burgers[vainqueur]);
        }
        
        // MINIMAX SI IL N'EXISTE PAS DE VAINQUEUR DE CONDORCET
        vainqueur = condorcet(matricePoids, fichierLog);
        if(vainqueur == -1){
            vainqueur = condorcetMinimax(matricePoids, fichierLog, NB_DUELS);
            printf("Mode de scrutin : Condorcet minimax , %d candidats, %d votants, vainqueur = %s\n", NB_CANDIDAT, NB_VOTANTS, burgers[vainqueur]);
        }else{
            printf("Mode de scrutin : Condorcet minimax , %d candidats, %d votants, vainqueur = %s\n", NB_CANDIDAT, NB_VOTANTS, burgers[vainqueur]);
        }
    }


    /*
     * LIBÉRATION DE LA MÉMOIRE ALLOUÉE
     *
     * Libère la mémoire allouée pour les différentes structures de données
     * à la fin de l'exécution du programme.
     */
    libererMatrice(matrice, MAX_VOTES_E);
    free(matrice);

    for (int i = 0; i < NB_CANDIDAT; i++) {
        free(matricePoids[i]);
    }
    free(matricePoids);

    for (int i = 0; i < MAX_VOTES_E; i++) {
        free(v_elect[i]);
    }

    free(v_elect);
    free(nb_elect);
    printf("\nFin d'éxecution du programme\n\n");
    return 0;
}
