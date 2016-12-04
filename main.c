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

#ifdef GRAPHICS
	#include <X11/Xlib.h>
	#include "graph.h"
#endif


#include "initialiser.h"
#include "myUtils.h"
#include "executionThreads.h"
#include "timeCalcule.h"



int main(int argc, char* argv[]){
#ifdef GRAPHICS
	XInitThreads();
#endif

	int ch;
	int mesure = 0;


	Terrain terrain;
	initialiserTerrain(&terrain);

	int nombreDePersonnes=10; // Nombre de personnes par défaut
	int optionThread = 0;
	int optionEtap = 1;
	int (*scenario)(Terrain*); // Pointeur sur fonction qui permettra d'indiquer quel scenario effectuer

	// Lecture des arguments
	while((ch = getopt(argc,argv,"mp:t:e:")) != -1){
		switch(ch){
		case 'm': mesure = 1; break;
		case 'p':
			nombreDePersonnes = pow(2,(optarg[0]-'0'));
			break;
		case 't': optionThread = atoi(optarg); break;
		case 'e': optionEtap = atoi(optarg); break;
		default: printf("Options invalides\n");
		}
	}
	printf("%d personnes\n", nombreDePersonnes);

	switch(optionEtap){
	case 1:
		switch(optionThread){
		case 0:
			printf("Etape 1: 1 seul thread\n");
			scenario = monoThread_e1;
			break;
		case 1:
			printf("Etape 1: Terrain divise en 4 threads\n");
			scenario = quatreThreads_e1;
			break;
		case 2:
			printf("Etape 1: 1 thread par personne\n");
			scenario = multiThread_e1;
			break;
		default:
			printf("Etape 1: 1 seul thread\n");
			scenario = monoThread_e1;
		}
		break;
	case 2:
		switch(optionThread){
		case 0:
			printf("Etape 2: 1 seul thread\n");
			scenario = monoThread_e2;
			break;
		case 1:
			printf("Etape 2: Terrain divise en 4 threads\n");
			scenario = quatreThreads_e2;
			break;
		case 2:
			printf("Etape 2: 1 thread par personne\n");
			scenario = multiThread_e2;
			break;
		default:
			printf("Etape 2: 1 seul thread\n");
			scenario = monoThread_e2;
		}
		break;
	default:
		printf("Etape 1: 1 seul thread\n");
		scenario = monoThread_e1;
		break;
	}


	// Creation des personnes sur le terrain
	terrain.nbPersonnes = nombreDePersonnes;
	terrain.personnes = (Personne*)malloc(sizeof(Personne)*nombreDePersonnes);
	genererPersonnes(&terrain, nombreDePersonnes);

#ifdef GRAPHICS
	int gd = DETECT, gm;
	initgraph(&gd,&gm,0);
	dessinTerrain(&terrain);
	mesure = 0;
	sleep(1);
#endif

	if(mesure == 1){

		double cpu_time, t_cpu[5], t_calcule[3];
		double usr_time, t_usr[5];
		printf("Option mesures\n");

		struct timeval user;
		for(int i = 0; i < 5; i++){
			printf("Execution %d\n", i+1);

			gettimeofday(&user, NULL);
			usr_time = user.tv_usec;
			cpu_time = clock();

			(*scenario)(&terrain);

			t_cpu[i] = clock() - cpu_time;
			gettimeofday(&user, NULL);
			t_usr[i] = user.tv_usec - usr_time;

			//printf("cpu = %f\tusr = %f\n", t_cpu[i]/CLOCKS_PER_SEC, t_usr[i]/pow(10,6));
		}
		detectTime(t_cpu, t_calcule);
		double cpu_avrg = calculeTime( t_calcule);
		detectTime(t_usr, t_calcule);
		double usr_avrg = calculeTime( t_calcule);
		printf( "Temps consommation CPU moyen : %f secondes\n", cpu_avrg/ CLOCKS_PER_SEC);
		printf( "Temps utilisateur moyen : %f secondes\n", usr_avrg/ pow(10,6));

	}
	else{
		(*scenario)(&terrain);
	}

#ifdef GRAPHICS
	getch();
	closegraph();
#endif

	free(terrain.personnes);

    return 0;
}





