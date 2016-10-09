/*
 * initialiser.c
 *
 *  Created on: 6 oct. 2016
 *      Author: Xiaohan Huang et Gaspard Lacroix
 */

#include <time.h>
#include <stdlib.h>

#include "myUtils.h"

void getPosition(int positions[]){
	positions[0] = rand()%124;
	positions[1] = (rand()%381) +128;
}

int initCheckfree(Terrain *terrain, int *p){
	int free = 1;
	int pligne = p[0];
	int pcolonne = p[1];
	for(int i = pligne; i < pligne + 4; i++)
		for(int j = pcolonne; j < pcolonne + 4; j++){
			if(terrain->surface[i][j] != -1)
				free = 0;
		}
	return free;
}

void genererPersonnes(Terrain *terrain, int nbPersonnes){

	int personnesPlacees = 0;
	int positions[2];
	srand(time(0));

	while(personnesPlacees < nbPersonnes){
		do{
			getPosition(positions);
		}while( !initCheckfree(terrain,positions) );
		//printf("%d,%d\n",positions[0],positions[1]);

		int pligne = positions[0];
		int pcolonne = positions[1];

		terrain->personnes[personnesPlacees].x = pcolonne;
		terrain->personnes[personnesPlacees].y = pligne;
		terrain->personnes[personnesPlacees].alive = 1;

		for(int i = pligne; i < pligne + 4; i++)
			for(int j = pcolonne; j < pcolonne + 4; j++){
				terrain->surface[i][j] = personnesPlacees;
			}
		//setcolor(RED);
		//rectangle(pcolonne+DECALAGE,pligne+DECALAGE,pcolonne+DECALAGE+3,pligne+DECALAGE+3);
		personnesPlacees++;
	}

}


void initialiserTerrain(Terrain *terrain){
	for(int i =0; i < LARGEUR; i++)
			for(int j = 0; j < LONGUEUR; j++)
				terrain->surface[i][j] = -1;

	// Haut du mur de gauche
	for(int i =0; i < 60; i++)
		for(int j = 0; j < 16; j++)
			terrain->surface[i][j] = -2;

	// Bas du mur de gauche
	for(int i = 68; i < 128; i++)
		for(int j = 0; j < 16; j++)
			terrain->surface[i][j] = -2;

	// Haut du mur de droite
	for(int i = 0; i < 56; i++)
		for(int j = 112; j < 128; j++)
			terrain->surface[i][j] = -2;

	// Bas du mur de droite
	for(int i = 72; i < 128; i++)
		for(int j = 112; j < 128; j++)
			terrain->surface[i][j] = -2;

}
