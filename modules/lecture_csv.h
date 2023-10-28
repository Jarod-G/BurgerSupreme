#ifndef LECTURE_CSV_H
#define LECTURE_CSV_H
#include "struct_data.h"

#define MAX_CHAR_SIZE 512
#define MAX_VOTES_E 50

void lireFichierCSV(const char* fichierVotesElecteurs,voteElecteur *v_elect[MAX_VOTES_E]);
#endif // LECTURE_CSV_H
