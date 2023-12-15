/**
 * @file condorcet.c
 * @author Gineste Jarod
 * @brief Ce fichier est le fichier principal pour tester différentes fonctions de méthodes Condorcet.
 * @version 0.1
 * @date 2023-11-25
 */

#include "condorcet.h"
#include "lecture_csv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * @brief Applique la méthode Condorcet Schulze pour déterminer le gagnant du vote.
 * @param duelsMatrice Matrice des résultats des duels entre les candidats.
 */
void condorcetSchulze(int **duelsMatrice) {
    int strength[NB_CANDIDAT][NB_CANDIDAT];

    // Initialiser la matrice de force à 0
    for (int i = 0; i < NB_CANDIDAT; i++) {
        for (int j = 0; j < NB_CANDIDAT; j++) {
            strength[i][j] = 0;
        }
    }

    // Calculer la matrice de force
    for (int i = 0; i < NB_CANDIDAT; i++) {
        for (int j = 0; j < NB_CANDIDAT; j++) {
            if (i != j) {
                for (int k = 0; k < NB_CANDIDAT - 1; k++) {
                    if (duelsMatrice[i][k] > duelsMatrice[j][k]) {
                        strength[i][j]++;
                    }
                }
            }
        }
    }

    // Trouver le gagnant du vote Condorcet Schulze
    for (int candidat = 0; candidat < NB_CANDIDAT; candidat++) {
        int estGagnant = 1;  // Supposons initialement que le candidat est le gagnant

        for (int adversaire = 0; adversaire < NB_CANDIDAT; adversaire++) {
            if (candidat != adversaire && strength[candidat][adversaire] < strength[adversaire][candidat]) {
                estGagnant = 0;  // Le candidat a perdu face à au moins un adversaire
                break;
            }
        }

        if (estGagnant) {
            printf("Le gagnant du vote Condorcet Schulze est %s\n", burgers[candidat]);
            break;
        }
    }
}

/**
 * @brief Élimine les candidats non inclus dans l'ensemble de Schwartz.
 * @param duelsMatrice Matrice des résultats des duels entre les candidats.
 * @param schwartzSet Tableau représentant l'ensemble de Schwartz.
 */
void ensembleSchwartz(int **duelsMatrice, int schwartzSet[NB_CANDIDAT]) {
    int hasEdges = 1;

    while (hasEdges) {
        // Vérifier s'il reste des arcs dans le graphe (matrice)
        hasEdges = 0;

        // Éliminer les sommets qui n'appartiennent pas à l'ensemble de Schwartz
        for (int i = 0; i < NB_DUELS; i++) {
            for (int j = 0; j < NB_DUELS; j++) {
                if (i != j && schwartzSet[i] && schwartzSet[j]) {
                    if (duelsMatrice[i][j] < duelsMatrice[j][i]) {
                        hasEdges = 1;
                        schwartzSet[i] = 0; // Éliminer le candidat i
                    }
                }
            }
        }
    }
}

/**
 * @brief Applique la méthode Condorcet Schulze Schwartz pour déterminer le gagnant du vote.
 * @param duelsMatrice Matrice des résultats des duels entre les candidats.
 */
void condorcetSchulzeSchwartz(int **duelsMatrice) {
    int *schwartzSet = malloc(NB_DUELS * sizeof(int));

    // Initialisez le tableau avec des 1
    for (int i = 0; i < NB_DUELS; i++) {
        schwartzSet[i] = 1;
    }

    ensembleSchwartz(duelsMatrice, schwartzSet);

    // Trouver le gagnant du vote Condorcet Schulze
    for (int i = 0; i < NB_DUELS; i++) {
        if (schwartzSet[i]) {
            printf("Le gagnant du vote Condorcet Schulze Schwartz est %s\n", burgers[i]);
            break;
        }
    }
    free(schwartzSet);
}

void condorcetMinimax(int **duelsMatrice) {
    int minLocal=duelsMatrice[0][0];
    int meilleurmin=duelsMatrice[0][0];
    int posVainqueur=0;
    for (int candidat = 0; candidat < NB_CANDIDAT; candidat++){
        for (int duel = 0; duel < NB_DUELS; duel++){
            if(minLocal > duelsMatrice[candidat][duel]){
                minLocal = duelsMatrice[candidat][duel];
            }
        }
        if(minLocal < meilleurmin){
            meilleurmin = minLocal;
            posVainqueur = candidat;
        }
    }
    printf("Le gagnant de Condorcet (methode minimax) est %s",burgers[posVainqueur]);
}


int* identifierCycle(int matriceArc[5][5],int candidat){
    int file[NB_CANDIDAT];
    int sizeArc = 0;
    int visites[NB_CANDIDAT] = {0};
    file[0] = candidat;
    int size = 1;
    int *ArcsCycles = malloc(NB_CANDIDAT * sizeof(int));
    for (int i = 0; i < NB_CANDIDAT; i++) {
        ArcsCycles[i] = -1;
    }

    while (size != 0){
        int courant = file[0];
        for (int i = 1; i < NB_CANDIDAT; i++){
            file[i - 1] = file[i];
        }
        size -= 1;
        visites[courant] = 1;
        
        for (int i = 0; i < NB_CANDIDAT; i++){
            if(matriceArc[courant][i] > 0 && visites[i] == 0){
                file[size] = i;
                visites[i] = 1;
                size += 1;
            } else if(matriceArc[courant][i] > 0 &&  i == candidat){
                printf("courant = %d\n", courant);
                ArcsCycles[sizeArc] = courant;
                sizeArc += 1;
            }
        }
    }

    return ArcsCycles;
}


/**
 * @brief Applique la méthode Condorcet Paires pour déterminer le gagnant du vote.
 * @param duelsMatrice Matrice des résultats des duels entre les candidats.
 */

void condorcetPaires(int **duelsMatrice) {
    
    int gagnant = 0;
    int *ArcsCycles;
    int **ListeCycles;
    
    
    int matrice[5][5] = 
    {   {0,0,7,15,0},
        {5,0,0,21,0},
        {0,13,0,0,3},
        {0,0,11,0,0},
        {1,9,0,17,0}
    };
    for (int x = 0; x < NB_CANDIDAT; x++)
    {   
        printf("%d\n",x);
        ArcsCycles = identifierCycle(matrice, x);
        for (int i = 0; i < NB_CANDIDAT; i++)
        {
            printf("On a %d \n", ArcsCycles[i]);
            
        }
        free(ArcsCycles);
    }
    printf("Le gagnant du vote Condorcet Paires est : %s \n", burgers[gagnant]);
    
}

/**
 * @brief Calcule les résultats des duels entre les candidats.
 * @param v_elect Tableau de structures voteElecteur représentant les votes de chaque électeur.
 * @param maxElecteurs Nombre maximum d'électeurs.
 * @param duelsMatrice Matrice pour stocker les résultats des duels entre les candidats.
 */
void duelsCalculsArcs(voteElecteur *v_elect[], int maxElecteurs, int **duelsMatrice) {
    for (int candidat = 0; candidat < NB_CANDIDAT; candidat++) {
        int i_currentCandidat = 0;
        for (int currentCandidat = 0; currentCandidat < NB_CANDIDAT; currentCandidat++) {
            if (currentCandidat != candidat) {
                int nbWin = 0;
                int nbLoose = 0;
                for (int electeur = 0; electeur < maxElecteurs; electeur++) {
                    if (currentCandidat != candidat && v_elect[electeur]->votes_electeur[candidat] != v_elect[electeur]->votes_electeur[currentCandidat]) {
                        if (v_elect[electeur]->votes_electeur[candidat] != -1) {
                            if (v_elect[electeur]->votes_electeur[candidat] < v_elect[electeur]->votes_electeur[currentCandidat] || v_elect[electeur]->votes_electeur[currentCandidat] == -1) {
                                nbWin++;
                            } else {
                                nbLoose++;
                            }
                        } else {
                            nbLoose++;
                        }
                    }
                }
                if (nbWin > nbLoose) {
                    duelsMatrice[candidat][i_currentCandidat] = nbWin - nbLoose;
                }
                i_currentCandidat++;
            }
        }
    }
}


/**
 * @brief Calcule les résultats des duels entre les candidats.
 * @param v_elect Tableau de structures voteElecteur représentant les votes de chaque électeur.
 * @param maxElecteurs Nombre maximum d'électeurs.
 * @param duelsMatrice Matrice pour stocker les résultats des duels entre les candidats.
 */
void duelsCalculsArcsPaires(voteElecteur *v_elect[], int maxElecteurs, int **duelsMatrice) {
    for (int candidat = 0; candidat < NB_CANDIDAT; candidat++) {
        for (int currentCandidat = 0; currentCandidat < NB_CANDIDAT; currentCandidat++) {
            if (currentCandidat != candidat) {
                int nbWin = 0;
                int nbLoose = 0;
                for (int electeur = 0; electeur < maxElecteurs; electeur++) {
                    if (currentCandidat != candidat && v_elect[electeur]->votes_electeur[candidat] != v_elect[electeur]->votes_electeur[currentCandidat]) {
                        if (v_elect[electeur]->votes_electeur[candidat] != -1) {
                            if (v_elect[electeur]->votes_electeur[candidat] < v_elect[electeur]->votes_electeur[currentCandidat] || v_elect[electeur]->votes_electeur[currentCandidat] == -1) {
                                nbWin++;
                            } else {
                                nbLoose++;
                            }
                        } else {
                            nbLoose++;
                        }
                    }
                }
                if (nbWin > nbLoose) {
                    duelsMatrice[candidat][currentCandidat] = nbWin - nbLoose;
                }
            }
        }
    }
}


/**
 * @brief Applique la méthode Condorcet pour déterminer le gagnant du vote.
 * @param duelsMatrice Matrice des résultats des duels entre les candidats.
 */
void condorcet(int **duelsMatrice) {
    int wins[NB_CANDIDAT] = {0};

    // Calculer le nombre total de duels remportés par chaque candidat
    for (int i = 0; i < NB_CANDIDAT; i++) {
        for (int j = 0; j < NB_DUELS; j++) {
            if (duelsMatrice[i][j] > 0) {
                wins[i] += 1;
            }
        }
    }

    // Trouver le candidat avec le plus grand nombre de duels remportés
    int winner = -1;
    for (int i = 0; i < NB_CANDIDAT; i++) {
        if (wins[i] == 9) {
            winner = i;
        }
    }
    if (winner == -1) {
        printf("Il n'y a pas de gagnant de Condorcet\n");
    } else {
        printf("Le gagnant du vote Condorcet est %s\n", burgers[winner]);
    }
}

/**
 * @brief Fonction principale pour tester les différentes méthodes Condorcet.
 * @return 0 en cas de succès.
 */
int main() {
    voteElecteur **v_elect = malloc(MAX_VOTES_E * sizeof(voteElecteur));
    nbElecteurs *nb_elect = malloc(sizeof(nbElecteurs));

    char* fichierBallots = "/home/jarod/Documents/projet/BurgerSupreme/data/VoteCondorcet.csv";

    lireFichierCSV_vote(fichierBallots, v_elect, nb_elect);

    // Allouez de la mémoire pour la matrice dynamique
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
    

    condorcet(matricePoids);
    condorcetSchulze(matricePoids);
    //condorcetSchulzeSchwartz(matricePoids);
    condorcetPaires(matriceArcsP);

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