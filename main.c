/*
 * main.c
 *
 *  Created on: 28 sept. 2016
 *      Author: huang & lacroix
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <math.h>

#include "initialiser.h"
#include "myUtils.h"
#include "executionThreads.h"
#include "graph.h"



int main(int argc, char* argv[]){
	int ch;
	//int gd = DETECT, gm = VGAMAX;
	//initgraph(&gd,&gm,0);

	Terrain terrain;
	initialiserTerrain(&terrain);

	int nombreDePersonnes=10; // Nombre de personnes par défaut
	int optionThread = 0;

	// Lecture des arguments
	while((ch = getopt(argc,argv,"mp:t:")) != -1){
		switch(ch){
		case 'm': printf("Execute option -m\n"); break;
		case 'p':
			nombreDePersonnes = pow(2,(optarg[0]-'0'));
			break;
		case 't': optionThread = atoi(optarg); break;
		default: printf("Options invalides\n");
		}
	}

	// Creation des personnes sur le terrain
	terrain.nbPersonnes = nombreDePersonnes;
	terrain.personnes = (Personne*)malloc(sizeof(Personne)*nombreDePersonnes);
	genererPersonnes(&terrain, nombreDePersonnes);

	//dessinTerrain(&terrain);

	switch(optionThread){
	case 0:
		monoThread(&terrain);
		break;
	default:
		monoThread(&terrain);
	}

	//getch();

	//closegraph();
	free(terrain.personnes);
	return 0;
}





