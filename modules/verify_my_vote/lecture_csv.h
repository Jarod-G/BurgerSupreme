/**
 * @file lecture_csv.h
 * @author Gineste Jarod
 * @brief this function read a csv file and put the data from it in a voteElecteur struct
 * @version 0.1
 * @date 2023-10-28
 * 
 */

#ifndef LECTURE_CSV_H
#define LECTURE_CSV_H

#include "struct_data.h"

#define MAX_CHAR_SIZE 512
#define MAX_VOTES_E 50

// Fonction qui récupère les informations d'un fichier csv de vote pour remplire une structure de voteElecteur
void lireFichierCSV_vote(const char *nomFichier, voteElecteur **v_elect,nbElecteurs* nb_elect);

// Fonction qui récupère les informations d'un fichier csv de vote pour remplire une structure de Electeur
void lireFichierCSV_electeur(const char* nomFichier, electeur **electeurs,nbElecteurs* nb_elect);
#endif // LECTURE_CSV_H
