/**
 * @file condorcet.h
 * @brief Définition des fonctions liées à la méthode de Condorcet et ses variantes.
 * @author Gineste Jarod
 * @date 2023-12-14
 */

#ifndef CONDORCET_H
#define CONDORCET_H

#include "struct_data.h"

/**
 * @brief Calcule les résultats des duels entre les candidats.
 * @param v_elect Tableau de structures voteElecteur représentant les votes de chaque électeur.
 * @param maxElecteurs Nombre maximum d'électeurs.
 * @param duelsMatrice Matrice pour stocker les résultats des duels entre les candidats.
 */
void duelsCalculsArcs(voteElecteur *v_elect[], int maxElecteurs, int **duelsMatrice);


/**
 * @brief Calcule les duels et les arcs pondérés à partir d'une matrice de votes.
 *
 * @param matrice Matrice de votes des électeurs
 * @param maxElecteurs Nombre maximum d'électeurs
 * @param duelsMatrice Matrice des résultats des duels et arcs pondérés
 */
void duelsCalculsArcsMatrice(int **matrice, int maxElecteurs, int **duelsMatrice);


/**
 * @brief Applique la méthode Condorcet pour déterminer le gagnant du vote.
 * @param duelsMatrice Matrice des résultats des duels entre les candidats.
 * @param fichierLog Fichier de log.
 * @return l'indice du gagnant Condorcet ou -1 s'il n'y a pas de gagnant.
 */
int condorcet(int **duelsMatrice,const char* fichierLog);


/**
 * @brief Applique la méthode Condorcet Schulze pour déterminer le gagnant du vote.
 * @param duelsMatrice Matrice des résultats des duels entre les candidats.
 * @param fichierLog Fichier de log.
 * @return l'indice du gagnant Condorcet Schulze ou -1 s'il n'y a pas de gagnant.
 */
int condorcetSchulze(int **duelsMatrice,const char* fichierLog, int NB_DUELS);


/**
 * @brief Applique la méthode Condorcet Minimax pour déterminer le gagnant du vote.
 * @param duelsMatrice Matrice des résultats des duels entre les candidats.
 * @param fichierLog Fichier de log.
 * @return l'indice du gagnant Condorcet Minimax ou -1 s'il n'y a pas de gagnant.
 */
int condorcetMinimax(int **duelsMatrice, const char* fichierLog, int NB_DUELS);


/**
 * @brief Trouve le gagnant selon la méthode de Condorcet avec résolution du paradoxe (fonction d'interface).
 * @param matrice Matrice des scores des candidats.
 * @param fichierLog Fichier de log.
 * @return Identifiant du candidat gagnant.
 */
int condorcetPaires(int **matrice,const char* fichier_log);

#endif /* CONDORCET_H */
