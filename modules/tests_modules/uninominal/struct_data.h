/**
 * @file lecture_csv.c
 * @author Gineste Jarod
 * @brief header file with data structures used in REV
 * @version 0.1
 * @date 2023-10-28
 * 
 */

#ifndef STRUCT_DATA_H
#define STRUCT_DATA_H
#include <stdlib.h>

/*----------------------------VARS GLOBALS----------------------------*/
#define NB_CANDIDAT 10
extern int NB_DUELS;  // Déclaration de la constante
extern const char *burgers[10];  // Déclaration de la constante
/*--------------------------------------------------------------------*/


// Déclaration de la structure pour les données CSV
typedef struct {
    int votes_electeur[10]; // 10 choix
    int reponse;
    char *date;
    char *cours;
    char *hash;
}voteElecteur;


typedef struct {
    char *clef;
    int num_electeur;
}electeur;


typedef struct {
    int nb_electeur;
}nbElecteurs;


// Déclaration de la structure de la matrice dynamique
typedef struct {
    int nbCandidats;
    int nbDuels;
    int ***matrice;
}MatriceDynamique;

void initialiserMatrice(MatriceDynamique *matriceDyn, int nbCandidats, int nbDuels);
void libererMatrice(MatriceDynamique *matriceDyn);

#endif // STRUCT_DATA_H
