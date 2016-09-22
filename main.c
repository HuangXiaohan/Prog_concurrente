/*
 * main.c
 *
 *  Created on: 22 sept. 2016
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "myUtils.h"


void initialiserTerrain(Terrain *terrain){
	for(int i =0; i < LARGEUR; i++)
		for(int j = 0; j < LONGUEUR; j++)
			terrain->surface[i][j] = 0;

	// Haut du mur de gauche
	for(int i =0; i < 60; i++)
		for(int j = 0; j < 16; j++)
			terrain->surface[i][j] = 1;

	// Bas du mur de gauche
	for(int i = 68; i < 128; i++)
		for(int j = 0; j < 16; j++)
			terrain->surface[i][j] = 1;

	// Haut du mur de droite
	for(int i = 0; i < 56; i++)
		for(int j = 112; j < 128; j++)
			terrain->surface[i][j] = 1;

	// Bas du mur de droite
	for(int i = 72; i < 128; i++)
		for(int j = 112; j < 128; j++)
			terrain->surface[i][j] = 1;
}

void genererPersonnes(Terrain *terrain, int nbPersonnes){

	srand(time(0));

	int personnesPLacees = 0;

	while(personnesPLacees < nbPersonnes){
		int posLargeur = rand()%124;
		int posLongueur = (rand()%381) +128;

		// TODO ajouter personnes

		personnesPLacees++;
	}

}


/*void afficherTerrain(Terrain *terrain){
	for(int i = 0; i < 128; i++){
		for(int j = 0; j < 128; j++)
			printf("%d", terrain->surface[i][j]);

		putchar('\n');

	}
}*/

int main(int argc, char* argv[]){

	Terrain terrain;

	initialiserTerrain(&terrain);

	genererPersonnes(&terrain, 50);


	return 0;
}
