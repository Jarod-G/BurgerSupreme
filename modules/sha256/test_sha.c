#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sha256.h"
#include "sha256_utils.h"
#define STRLONG 60

int main(){
    int bufferSize = SHA256_BLOCK_SIZE;
    char hashRes[bufferSize*2 + 1]; // contiendra le hash en hexadécimal
    char *item = malloc(STRLONG * sizeof(char)); // contiendra la chaîne à hasher

    // Utilisez une chaîne plus courte à copier
    strcpy(item, "Exemple de chaîne à hasher.");

    sha256ofString((BYTE *)item, hashRes); // hashRes contient maintenant le hash de l'item
    int long_hash = strlen(hashRes); // sa longueur en caractères hexadécimaux
    printf("Le sha : %s avec %d caractères hexadécimaux, soit %d octets comme prévu\n", hashRes, long_hash, long_hash / 2);

    free(item); // N'oubliez pas de libérer la mémoire lorsque vous avez terminé.

    return 0;
}
