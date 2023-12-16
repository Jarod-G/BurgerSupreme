/**
 * @file uninominial.c
 * @author Handwerk Hippolyte
 * @author Gineste Jarod
 * @brief this function gives the winner of the uninominal election (1 or 2 round)
 * @version 0.1
 * @date 2022-11-18
 */

#include "uninominal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int *resultatPremierTour(voteElecteur *voteElecteur[], int nbCandidat,int nbElecteur,FILE * fptr) {
  /**
  * @brief This function gives the results of the first round in a tab 
  * 
  * @param voteElecteur from struct_data.h
  * @param nbCandidat nombre de candidat à l'election
  * @param nbElecteur nombre d' electeur à l'election
  * @return int* tableau de taille nbCandidat qui contient le nombre de vote pour chaque candidat
  */
  int *resultat = malloc(nbCandidat * sizeof(int));

  // Initialiser le tableau resultat à zéro
  for (int i = 0; i < nbCandidat; i++) {
    resultat[i] = 0;
  }
  for (int i = 0; i < nbElecteur; i++) {//pour chaque electeur
    for (int j = 0; j < nbCandidat; j++) {
      if (voteElecteur[i]->votes_electeur[j] == 1) {//on regarde si le candidat a recu son vote 1
        resultat[j] += 1;//si oui on ajoute un vote dans la colonne correspondante
      }
    }
  }
  //log
  fprintf(fptr,"resultat premier tour \n");
  for(int i=0;i<nbCandidat;i++)
  fprintf(fptr,"%s %d votes (%0.2f %%)||",burgers[i],resultat[i],((float)resultat[i]/nbElecteur)*100);
  fprintf(fptr,"\n");

  return resultat;
}

int *resultatSecondTour(voteElecteur *voteElecteur[], int posPremier, int posDeuxieme, int nbElecteur,FILE * fptr) {
    /**
    * @brief This function gives the results of the second round in a tab 
    * 
    * @param voteElecteur from struct_data.h
    * @param nbCandidat nombre de candidat à l'election
    * @param nbElecteur nombre d' electeur à l'election
    * @return int* tableau de taille 2 qui contient la pos du gagnant et le nombre de vote
    */
  int resultat[2];
  resultat[0]=0;
  resultat[1]=0;
  for (int i = 0; i < nbElecteur; i++) {//pour chaque electeur
    if (voteElecteur[i]->votes_electeur[posPremier] <
        voteElecteur[i]->votes_electeur[posDeuxieme]) {//on regarde si le premier candidat est mieux classe que le deuxieme afin de faire le report de voix
      resultat[0]++;//si oui le candidat 1 gagne une voix
    } else {
      resultat[1]++;//sinon c'est le candidat 2 qui gagne une voix
    }
  }
  //log
  fprintf(fptr,"resultat second tour \n");
  for(int i=0;i<2;i++)
  fprintf(fptr,"%s %d votes (%0.2f %%)||",burgers[i],resultat[i],((float)resultat[i]/nbElecteur)*100);
  fprintf(fptr,"\n");

  if (resultat[0] > resultat[1]) {
    int *res = malloc(2 * sizeof(int));
    res[0] = posPremier;
    res[1] = resultat[0];
    return res;
  } else {
    int *res = malloc(2 * sizeof(int));
    res[0] = posDeuxieme;
    res[1] = resultat[1];
    return res;
  }
}

void uninominal1tour(voteElecteur **voteElecteur, int nbElecteur,const char* fichierLog) {
    /**
    * @brief This function gives the winner in First-past-the-post voting
    * @param voteElecteur from struct_data.h
    * @param nbCandidat nombre de candidat à l'election
    * @param nbElecteur nombre d' electeur à l'election
    */
  FILE *fptr= fopen(fichierLog,"a");
  fprintf(fptr,"UNINOMINAL A 1 TOUR");
  
  int *resultat = resultatPremierTour(voteElecteur, NB_CANDIDAT, nbElecteur,fptr);
  int scoreVainqueur = resultat[0];//on cherche le candidat avec le maximum de voix
  int posVainqueur = 0;
  
  for (int i = 1; i < NB_CANDIDAT; i++) {
    if (resultat[i] > scoreVainqueur) {
      scoreVainqueur = resultat[i];
      posVainqueur = i;
    }
  }

  fprintf(fptr,"Le vainqueur est le %s avec %d votes soit %0.2f%%\n\n", burgers[posVainqueur],resultat[posVainqueur], ((float)resultat[posVainqueur]/(float)nbElecteur)*100);//on donne les resultats du premier tour
  printf("Mode de scrutin : uninominal à un tour, %d candidats, %d votants, vainqueur = %s, score = %0.f%%\n", NB_CANDIDAT, nbElecteur,  burgers[posVainqueur], ((float)resultat[posVainqueur]/(float)nbElecteur)*100);
  
  free(resultat);
  fclose(fptr);
}

void uninominal2tour(voteElecteur **voteElecteur, int nbElecteur,const char* fichierLog) {
    /**
    * @brief This function gives the winner in Two-round system voting
    * @param voteElecteur from struct_data.h
    * @param nbCandidat nombre de candidat à l'election
    * @param nbElecteur nombre d' electeur à l'election
    */
    FILE *fptr= fopen(fichierLog,"a");
    fprintf(fptr,"UNINOMINAL A 2 TOUR");
    int *resultat = resultatPremierTour(voteElecteur, NB_CANDIDAT, nbElecteur,fptr);

    int posPremier = 0;//on cherche les deux candidats avec le plus de voix
    int posDeuxieme = 1;

    if (resultat[posPremier] < resultat[posDeuxieme]) {
        // Échanger les positions si le deuxième a un score plus élevé que le premier
        posPremier = 1;
        posDeuxieme = 0;
    }

    for (int i = 2; i < NB_CANDIDAT; ++i) {
        if (resultat[i] > resultat[posPremier]) {//si resultat[i] est plus grand que le premier le premier devient deuxieme et resultat[i] devient premier
            posDeuxieme = posPremier;
            posPremier = i;
        } else if (resultat[i] > resultat[posDeuxieme]) {//si resultat[i] est plus grand que le deuxieme, resultat[i] devient deuxieme
            posDeuxieme = i;
        }
    }

    printf("Mode de scrutin : uninominal à deux tours, tour 1, %d candidats, %d votants, vainqueur = %s, score = %0.f%%\n", NB_CANDIDAT, nbElecteur, burgers[posPremier], ((float)resultat[0]/(float)nbElecteur)*100);
    printf("Mode de scrutin : uninominal à deux tours, tour 1, %d candidats, %d votants, vainqueur = %s, score = %0.f%%\n", NB_CANDIDAT, nbElecteur, burgers[posDeuxieme], ((float)resultat[1]/(float)nbElecteur)*100);

    int *res = resultatSecondTour(voteElecteur, posPremier, posDeuxieme, nbElecteur,fptr  );
    fprintf(fptr,"Le vainqueur est %s (%d votes) avec %0.2f%%\n\n", burgers[res[0]], res[1], ((float)res[1]/(float)nbElecteur)*100);//on donne les resultats du second tour
    
    printf("Mode de scrutin : uninominal à deux tours, tour 2, %d candidats, %d votants, vainqueur = %s, score = %0.f%%\n", NB_CANDIDAT, nbElecteur, burgers[res[0]], ((float)res[1]/(float)nbElecteur)*100);//on donne les resultats du second tour

    free(res);
    free(resultat);
    fclose(fptr);

}