/**
 * @file test.c
 * @author Barcelo Fanny
 * @brief Programme principale qui texte les différentes fonctions de votes
 * @version 0.1
 * @date 2023-12-14
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>
#include <ctype.h>
#include <assert.h>

#include "lecture_csv.h"
#include "condorcet.h"
#include "jugementMajoritaire.h"
#include "uninominal.h"
#include "condorcet.h"

void testDuelsCalculsArc(voteElecteur *v_elect[], int maxElecteurs, int **duelsMatrice, int ** resultatAttendu){
	printf("............................................\n");
	printf("Début du test du calcul des Arcs de duel \n");
	
	duelsCalculsArcs(v_elect, maxElecteurs, duelsMatrice);
	
	if(duelsMatrice == resultatAttendu ){
		printf("Test Calculs Arc Duel OK \n");
	}
	else {
		printf("Calculs Arc Duel non valide \n");
	}
	printf("............................................\n");
}

void testDuelsCalculsArcPaires(voteElecteur *v_elect[], int maxElecteurs, int **duelsMatrice, int** resultatAttendu){
	printf("............................................\n");
	printf("Début du test du calcul des Arcs de duel pour le Condorcetv Paires \n");
	
	duelsCalculsArcs(v_elect, maxElecteurs, duelsMatrice);
	
	if(duelsMatrice == resultatAttendu ){
		printf("Test Calculs Arc Duel Paires OK \n");
	}
	else {
		printf("Calculs Arc Duel Paires non valide \n");
	}
	printf("............................................\n");
}

void testUni1 (voteElecteur **voteElecteur, int nbElecteur,const char* fichierLog, char* resultatAttendu){
	printf("............................................\n");
	printf("Début du test du vote uninominal à 1 tour \n");
	
	const char* resultat = uninominal1tour(voteElecteur, nbElecteur, fichierLog);
	
	if(strcmp(resultat, resultatAttendu)==0 ){
		printf("Test Uninominal à 1 tour OK \n");
	}
	else {
		printf("Uninominal à 1 tour non valide \n");
	}
	printf("............................................\n");
}

void testUni2(voteElecteur **voteElecteur, int nbElecteur,const char* fichierLog, char* resultatAttendu){
	printf("............................................\n");
	printf("Début du test du vote uninominal à 2 tour \n");
	
	const char* resultat = uninominal2tour(voteElecteur, nbElecteur, fichierLog);
	
	if( strcmp(resultat, resultatAttendu)==0 ){
		printf("Test Uninominal à 2 tour OK \n");
	}
	else {
		printf("Uninominal à 2 tour non valide \n");
	}
	printf("............................................\n");
}

void testJugementMajoritaire(voteElecteur **votes, int nbVotants, const char *fichierLog, char* resultatAttendu){
	printf("............................................\n");
	printf("Début du test du jugement majoritaire \n");
	
	const char* resultat = jugementMajoritaire(votes, nbVotants, fichierLog);
	
	if( strcmp(resultat, resultatAttendu)==0 ){
		printf("Test jugement majoritaire OK \n");
	}
	else {
		printf("jugement majoritaire non valide \n");
	}
	printf("............................................\n");
}

void testCondorcet(int **duelsMatrice, const char *fichierLog, int resultatAttendu){
	printf("............................................\n");
	printf("Début du test du vainqueur de Condorcet\n");
	
	int resultat = condorcet(duelsMatrice, fichierLog);
	if(resultat == resultatAttendu ){
		printf("Test Condorcet OK \n");
	}
	else {
		printf("Condorcet non valide \n");
	}
	printf("............................................\n");
}

void testCondorcetMinimax(int **duelsMatrice, const char *fichierLog, int resultatAttendu, int NB_DUELS){
	printf("............................................\n");
	printf("Début du test du vainqueur de Condorcet avec la méthode minimax\n");
	
	int resultat = condorcetMinimax(duelsMatrice, fichierLog, NB_DUELS);
	if(resultat == resultatAttendu ){
		printf("Test Condorcet Minimax OK \n");
	}
	else {
		printf("Condorcet Minimax non valide \n");
	}
	printf("............................................\n");
}

void testCondorcetSchulze(int **duelsMatrice, const char *fichierLog, int NB_DUELS,int resultatAttendu){
	printf("............................................\n");
	printf("Début du test du vainqueur de Condorcet avec la méthode Schulze\n");
	
	int resultat = condorcetSchulze(duelsMatrice, fichierLog, NB_DUELS);
	if(resultat == resultatAttendu ){
		printf("Test Condorcet Schulze OK \n");
	}
	else {
		printf("Condorcet Schulze non valide \n");
	}
	printf("............................................\n");
}

void testCondorcetPaires(int **grapheDuels, const char *fichierLog, int resultatAttendu){
	printf("............................................\n");
	printf("Début du test du vainqueur de Condorcet avec la méthode Paires\n");
	
	int resultat = condorcetPaires(grapheDuels,fichierLog);
	if(resultat == resultatAttendu ){
		printf("Test Condorcet Paires OK \n");
	}
	else {
		printf("Condorcet Paires non valide : résultat de la fonction : %d, résultat attendu : %d\n", resultat, resultatAttendu);
	}
	printf("............................................\n");
}

int main(){
	char * fichierLog = "log.txt";	
	char* fichierBallots = "data_csv/jugement.csv";
	
	/*------------------FICHIER BALLOTS TESTS------------------*/
	voteElecteur **v_elect = malloc(MAX_VOTES_E * sizeof(voteElecteur));
	nbElecteurs *nb_elect = malloc(sizeof(nbElecteurs));
	matriceTab* matrice = malloc(sizeof(matriceTab));
	matriceTab* matricePoids = malloc(sizeof(matriceTab));

	lireFichierCSV_vote(fichierBallots, v_elect, nb_elect);	
	
	testUni1(v_elect, nb_elect->nb_electeur, fichierLog, "Crispy");
	printf("\n \n");
	
	testUni2(v_elect, nb_elect->nb_electeur, fichierLog,"Cheese Burger");
	printf("\n \n");
	
	testJugementMajoritaire(v_elect,nb_elect->nb_electeur,fichierLog, "Burger Black Pepper");
	printf("\n\n");
	
	/*------------------MATRICE WIKI TEST------------------*/

	initialiserMatrice(matrice, MAX_VOTES_E, MAX_CANDIDATS);
	initialiserMatrice(matricePoids, MAX_VOTES_E, MAX_CANDIDATS);

	lireMatriceCSV("data_csv/wiki_paires.csv",matrice);
	
	duelsCalculsArcsMatrice(matrice->tab, nb_elect->nb_electeur, matricePoids->tab);
	
	testCondorcet(matricePoids->tab, fichierLog, -1);
	printf("\n\n");
	
	testCondorcetMinimax(matricePoids->tab, fichierLog, 0, NB_CANDIDAT);
	printf("\n\n");
	
	testCondorcetSchulze(matricePoids->tab, fichierLog, NB_CANDIDAT,4);
	printf("\n\n");

	testCondorcetPaires(matrice->tab, fichierLog, 0);
	printf("\n\n");
	
	for (int i = 0; i < MAX_VOTES_E; i++) {
    	free(v_elect[i]);
	}
	free(v_elect);
	free(nb_elect);
	
	libererMatrice(matrice,MAX_VOTES_E);
	libererMatrice(matricePoids,MAX_VOTES_E);

	return 0;
 }
