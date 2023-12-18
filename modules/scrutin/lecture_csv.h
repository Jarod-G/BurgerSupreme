/**
 * @file lecture_csv.h
 * @author Gineste Jarod
 * @brief .h du fichier lecture_csv.c qui gère lecture de fichiers CSV pour extraire et structurer les données
 * @date 2023-10-28
 */

#ifndef LECTURE_CSV_H
#define LECTURE_CSV_H

#include "struct_data.h"

#define MAX_CHAR_SIZE 512
#define MAX_VOTES_E 128
#define MAX_CANDIDATS 128

/**
 * @brief Lit un fichier CSV de votes et stocke les données dans une structure voteElecteur.
 * @param nomFichier Chemin du fichier CSV des votes
 * @param v_elect Tableau de structures voteElecteur pour stocker les données
 * @param nb_elect Structure pour stocker le nombre total d'électeurs
 */
void lireFichierCSV_vote(const char *nomFichier, voteElecteur **v_elect,nbElecteurs* nb_elect);

/**
 * @brief Lit un fichier CSV d'électeurs et stocke les données dans une structure electeur.
 * @param nomFichier Chemin du fichier CSV des électeurs
 * @param electeurs Tableau de structures electeur pour stocker les données
 * @param nb_elect Structure pour stocker le nombre total d'électeurs
 */
void lireFichierCSV_electeur(const char* nomFichier, electeur **electeurs,nbElecteurs* nb_elect);

/**
 * @brief Lit un fichier CSV de matrice de votes et stocke les données dans une structure matriceTab.
 * @param nomFichier Chemin du fichier CSV de la matrice de votes
 * @param matrice Structure matriceTab pour stocker les données
 */
void lireMatriceCSV(const char *nomFichier, matriceTab *matrice);
#endif // LECTURE_CSV_H
