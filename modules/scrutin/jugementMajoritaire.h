/**
 * @file jugementMajoritaire.h
 * @brief Définition des fonctions liées au jugement.
 * @author Handwerk Hippolyte
 * @date 2023-12-16
 */
#ifndef JUGEMENT_MAJORITAIRE_H
#define JUGEMENT_MAJORITAIRE_H

#include "struct_data.h"
#include <stdio.h>

/**
 * @brief Fonction principale pour le jugement majoritaire
 * @param votes Tableau des votes des électeurs
 * @param nbVotants Nombre total d'électeurs
 * @param nbCandidat Nombre total de candidats
 * @param fichierLog Nom du fichier de sortie
 */
const char* jugementMajoritaire(voteElecteur **votes, int nbVotants, const char *fichierLog);


/**
 * @brief Fonction qui calcule l'appréciation d'un candidat
 * @param votes Tableau des votes des électeurs
 * @param numCandidat Numéro du candidat en cours d'évaluation
 * @param nbVotants Nombre total d'électeurs
 * @param fptr Pointeur vers le fichier de log
 * @return Tableau de deux floats [appreciation, score]
 */
float *appreciationCandidat(voteElecteur **votes,int numCandidat,int nbVotants,FILE *fptr);


#endif