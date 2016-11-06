/*
 * main.c
 *
 *  Created on: 28 sept. 2016
 *      Author: Xiaohan Huang et Gaspard Lacroix
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <math.h>

#include "initialiser.h"
#include "myUtils.h"
#include "executionThreads.h"
//#include "graph.h"
#include "timeCalcule.h"



int main(int argc, char* argv[]){
	int ch;
	double start, finish, t_execute[5], t_calcule[3];
	int mesure = 0;
	//int gd = DETECT, gm = VGAMAX;
	//initgraph(&gd,&gm,0);

	Terrain terrain;
	initialiserTerrain(&terrain);

	int nombreDePersonnes=10; // Nombre de personnes par défaut
	int optionThread = 0;

	// Lecture des arguments
	while((ch = getopt(argc,argv,"mp:t:")) != -1){
		switch(ch){
		case 'm': mesure = 1; break;
		case 'p':
			nombreDePersonnes = pow(2,(optarg[0]-'0'));
			break;
		case 't': optionThread = atoi(optarg); break;
		default: printf("Options invalides\n");
		}
	}
	printf("%d personnes\n", nombreDePersonnes);

	switch(optionThread){
	case 0:
		printf("1 seul thread\n");
		break;
	case 1:
		printf("Terrain divise en 4 threads\n");
		break;
	case 2:
		printf("1 thread par personnes\n");
		break;
	default:
		printf("1 seul thread\n");
	}

	// Creation des personnes sur le terrain
	terrain.nbPersonnes = nombreDePersonnes;
	terrain.personnes = (Personne*)malloc(sizeof(Personne)*nombreDePersonnes);
	genererPersonnes(&terrain, nombreDePersonnes);

	//dessinTerrain(&terrain);

	if(mesure == 1){
		printf("Option mesures\n");
		for(int i = 0; i < 5; i++){
			start = clock();
			switch(optionThread){
				case 0:
					monoThread(&terrain);
					break;
				case 2:
					multiThread(&terrain);
					break;
				case 1:
					quatreThreads(&terrain);
					break;
				default:
					monoThread(&terrain);
			}
			finish = clock();
			t_execute[i] = finish - start;
		}
		detectTime(t_execute, t_calcule);
		double t_avrg = calculeTime( t_calcule);
		printf( "Temps d'exécution moyen : %f secondes\n", t_avrg/ CLOCKS_PER_SEC);
	}
	else{
		switch(optionThread){
		case 0:
			monoThread(&terrain);
			break;
		case 2:
			multiThread(&terrain);
			break;
		case 1:
			quatreThreads(&terrain);
			break;
		default:
			monoThread(&terrain);
		}
	}


	//getch();

	//closegraph();
	free(terrain.personnes);
	return 0;
}





