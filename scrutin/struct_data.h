/**
 * @file struct_data.h
 * @author Gineste Jarod
 * @brief Définition de données structurées et fonctions associées
 * @date 2023-11-28
 */

#ifndef STRUCT_DATA_H
#define STRUCT_DATA_H
#include <stdlib.h>

/*----------------------------VARS GLOBALS----------------------------*/
extern int NB_CANDIDAT;
extern const char *burgers[10];
/*--------------------------------------------------------------------*/


/**
 * @struct voteElecteur
 * @brief Structure représentant les données CSV d'un fichier de bulletins de vote
 */
typedef struct {
    int votes_electeur[10]; // 10 choix
    int reponse;
    char *date;
    char *cours;
    char *hash;
}voteElecteur;


/**
 * @struct electeur
 * @brief Structure représentant les données CSV d'un fichier d'électeurs
 */
typedef struct {
    char *clef;
    int num_electeur;
}electeur;


/**
 * @struct nbElecteurs
 * @brief Structure représentant le nombre total d'électeurs
 */
typedef struct {
    int nb_electeur;
}nbElecteurs;


/**
 * @struct matriceTab
 * @brief Structure représentant une matrice d'entiers avec des noms de candidats
 */
typedef struct {
    int **tab;
    char *nomsCandidats;
    int nbCandidat;
    int nbElecteurs;
}matriceTab;


/**
 * @brief Initialise une matrice avec des zéros.
 * @param matrice Pointeur vers la structure matriceTab à initialiser
 * @param lignes Nombre de lignes dans la matrice
 * @param colonnes Nombre de colonnes dans la matrice
 */
void initialiserMatrice(matriceTab *matrice, int lignes, int colonnes);

/**
 * @brief Libère la mémoire allouée pour une matrice.
 * @param matrice Pointeur vers la structure matriceTab à libérer
 * @param lignes Nombre de lignes dans la matrice
 */
void libererMatrice(matriceTab *matrice, int lignes);

#endif // STRUCT_DATA_H
