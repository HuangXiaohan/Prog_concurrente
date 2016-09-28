/*
 * main.c
 *
 *  Created on: 22 sept. 2016
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "myUtils.h"
#include "monoThread.h"

void initialiserTerrain(Terrain *terrain);
int* getPosition();
int checkfree(Terrain *terrain,int *p);
void afficherTerrain(Terrain *terrain);

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

	int personnesPLacees = 0;
	int *position;
	srand(time(0));

	while(personnesPLacees < nbPersonnes){
		do{
			position = getPosition();
		}while(checkfree(terrain,position) != 1);
		//printf("%d,%d\n",position[0],position[1]);

		int pligne = position[0];
		int pcolonne = position[1];

		for(int i = pligne; i < pligne + 4; i++)
			for(int j = pcolonne; j < pcolonne + 4; j++){
				terrain->surface[i][j] = personnesPLacees+10;
			}

		personnesPLacees++;
	}

}

int checkfree(Terrain *terrain, int *p){
	int free = 1;
	int pligne = p[0];
	int pcolonne = p[1];
	for(int i = pligne; i < pligne + 4; i++)
		for(int j = pcolonne; j < pcolonne + 4; j++){
			if(terrain->surface[i][j] != 0)
				free = 0;
		}
	return free;
}

int* getPosition(){
	static int position[2];
	position[0] = rand()%124;
	position[1] = (rand()%381) +128;
	return position;
}


void afficherTerrain(Terrain *terrain){
	for(int i = 0; i < 128; i++){
		for(int j = 0; j < 512; j++)
			printf("%d", terrain->surface[i][j]);

		putchar('\n');

	}
}


int main(int argc, char* argv[]){
	Terrain terrain;

	initialiserTerrain(&terrain);

	genererPersonnes(&terrain, 50);

	//afficherTerrain(&terrain);

	monoThread();

	return 0;
}
