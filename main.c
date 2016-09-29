/*
 * main.c
 *
 *  Created on: 28 sept. 2016
 *      Author: huang & lacroix
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <getopt.h>
#include "graphics.h"
#include "myUtils.h"
#include "executionThreads.h"
#include <math.h>



void initialiserTerrain(Terrain *terrain){
	for(int i =0; i < LARGEUR; i++)
			for(int j = 0; j < LONGUEUR; j++)
				terrain->surface[i][j] = -1;
	rectangle(50,50,LONGUEUR+DECALAGE,LARGEUR+DECALAGE);
	//floodfill(LONGUEUR/2,LARGEUR/2,100,15);

	// Haut du mur de gauche
	for(int i =0; i < 60; i++)
		for(int j = 0; j < 16; j++)
			terrain->surface[i][j] = -2;
	rectangle(DECALAGE,DECALAGE,15+DECALAGE,59+DECALAGE);
	floodfill(60,100,4);

	// Bas du mur de gauche
	for(int i = 68; i < 128; i++)
		for(int j = 0; j < 16; j++)
			terrain->surface[i][j] = -2;
	rectangle(DECALAGE,68+DECALAGE,15+DECALAGE,127+DECALAGE);
	floodfill(60,120,4);

	// Haut du mur de droite
	for(int i = 0; i < 56; i++)
		for(int j = 112; j < 128; j++)
			terrain->surface[i][j] = -2;
	rectangle(112+DECALAGE,DECALAGE,127+DECALAGE,55+DECALAGE);
	floodfill(170,70,4);

	// Bas du mur de droite
	for(int i = 72; i < 128; i++)
		for(int j = 112; j < 128; j++)
			terrain->surface[i][j] = -2;
	rectangle(112+DECALAGE,72+DECALAGE,127+DECALAGE,127+DECALAGE);
	floodfill(170,130,4);

	//Sortie du mur de gauche
	for(int i = 60; i < 68; i++)
		for(int j = 0; j < 16; j++)
			terrain -> surface[i][j] = -3;

	//Sortie du mur de droite
	for(int i = 56; i < 72; i++)
		for(int j = 112; j < 128; j++)
			terrain -> surface[i][j] = -4;

}

void genererPersonnes(Terrain *terrain, int nbPersonnes){

	int personnesPlacees = 0;
	int positions[2];
	srand(time(0));

	while(personnesPlacees < nbPersonnes){
		do{
			getPosition(positions);
		}while( !checkfree(terrain,positions) );
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
		setcolor(RED);
		rectangle(pcolonne+DECALAGE,pligne+DECALAGE,pcolonne+DECALAGE+3,pligne+DECALAGE+3);
		personnesPlacees++;
	}

}

int checkfree(Terrain *terrain, int *p){
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

void getPosition(int positions[]){
	positions[0] = rand()%124;
	positions[1] = (rand()%381) +128;
}


int main(int argc, char* argv[]){
	int ch;
	int gd = DETECT, gm = VGAMAX;
	initgraph(&gd,&gm,0);

	Terrain terrain;

	initialiserTerrain(&terrain);

	int nombreDePersonnes=10; // Nombre de personnes par défaut


	while((ch = getopt(argc,argv,"mp:t:")) != -1){
		switch(ch){
		case 'm': printf("Execute option -m\n"); break;
		case 'p':
			nombreDePersonnes = pow(2,(optarg[0]-'0'));
			break;
		case 't': printf("Execute option -t%s\n",optarg); break;
		default: printf("Options invalides\n");
		}
	}


	terrain.nbPersonnes = nombreDePersonnes;
	terrain.personnes = (Personne*)malloc(sizeof(Personne)*nombreDePersonnes);
	genererPersonnes(&terrain, nombreDePersonnes);

	monoThread(&terrain);


	getch();
	closegraph();

	free(terrain.personnes);
	return 0;
}





