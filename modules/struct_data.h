#ifndef STRUCT_DATA_H
#define STRUCT_DATA_H

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

#endif // STRUCT_DATA_H
