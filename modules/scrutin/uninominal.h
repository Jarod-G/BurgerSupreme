/**
 * @file uninominial.h
 * @author Gineste Jarod
 * @brief Ces fonctions donnent le gagnant de l'élection uninominal (1 ou 2 tours)
 * @version 0.1
 * @date 2023-11-18
 */
#ifndef UNINOMINAL_H
#define UNINOMINAL_H

#include "struct_data.h"
/**
* @brief Cette fonction donne le gagnant de l'élection uninominal à 1 tour
* @param voteElecteur from struct_data.h
* @param nbCandidat nombre de candidat à l'election
* @param nbElecteur nombre d' electeur à l'election
*/
const char* uninominal1tour(voteElecteur **voteElecteur, int nbElecteur,const char* fichierLog);


/**
* @brief Cette fonction donne le gagnant de l'élection uninominal à 2 tours
* @param voteElecteur from struct_data.h
* @param nbCandidat nombre de candidat à l'election
* @param nbElecteur nombre d' electeur à l'election
*/
const char* uninominal2tour(voteElecteur **voteElecteur, int nbElecteur,const char* fichierLog);
#endif // UNINOMINAL_H