#ifndef STRUCT_DATA_H
#define STRUCT_DATA_H

#define MAX_COLS 100
#define MAX_CHAR_SIZE 50

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

// FAIRE UNE STRUCT QUI PREND LES DEUX !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#endif // STRUCT_DATA_H
