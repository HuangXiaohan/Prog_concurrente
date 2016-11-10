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

void excuteThread(int opEtap, int opThread, Terrain terrain){
	if(opEtap == 1){
		switch(opThread){
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
	else if(opEtap == 2){
		printf("lalalalala\n");
	}
}

int main(int argc, char* argv[]){
	int ch;
	int mesure = 0;
	//int gd = DETECT, gm = VGAMAX;
	//initgraph(&gd,&gm,0);

	Terrain terrain;
	initialiserTerrain(&terrain);

	int nombreDePersonnes=10; // Nombre de personnes par défaut
	int optionThread = 0;
	int optionEtap = 1;

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
			printf("Etap 1: 1 seul thread\n");
			break;
		case 1:
			printf("Etap 1: Terrain divise en 4 threads\n");
			break;
		case 2:
			printf("Etap 1: 1 thread par personnes\n");
			break;
		default:
			printf("Etap 1: 1 seul thread\n");
		}
		break;
	case 2:
		switch(optionThread){
		case 0:
			printf("Etap 2: 1 seul thread\n");
			break;
		case 1:
			printf("Etap 2: Terrain divise en 4 threads\n");
			break;
		case 2:
			printf("Etap 2: 1 thread par personnes\n");
			break;
		default:
			printf("Etap 2: 1 seul thread\n");
		}
		break;
	}


	// Creation des personnes sur le terrain
	terrain.nbPersonnes = nombreDePersonnes;
	terrain.personnes = (Personne*)malloc(sizeof(Personne)*nombreDePersonnes);
	genererPersonnes(&terrain, nombreDePersonnes);

	//dessinTerrain(&terrain);

	if(mesure == 1){

		double cpu_time, t_cpu[5], t_calcule[3];
		double usr_time, t_usr[5];
		printf("Option mesures\n");

		struct timeval user;
		for(int i = 0; i < 5; i++){
			printf("Execution %d\n", i+1);

			gettimeofday(&user, NULL);
			usr_time = user.tv_sec + user.tv_usec/pow(10,6);
			cpu_time = clock();

			excuteThread(optionEtap, optionThread, terrain);

			t_cpu[i] = clock() - cpu_time;
			gettimeofday(&user, NULL);
			t_usr[i] = user.tv_sec + (user.tv_usec/pow(10,6)) - usr_time;

			//printf("cpu = %f\tusr = %f\n", t_cpu[i]/CLOCKS_PER_SEC, t_usr[i]);
		}
		detectTime(t_cpu, t_calcule);
		double cpu_avrg = calculeTime( t_calcule);
		detectTime(t_usr, t_calcule);
		double usr_avrg = calculeTime( t_calcule);
		printf( "Temps consommation CPU moyen : %f secondes\n", cpu_avrg/ CLOCKS_PER_SEC);
		printf( "Temps utilisateur moyen : %f secondes\n", usr_avrg);

	}
	else{
		excuteThread(optionEtap, optionThread, terrain);
	}


	//getch();

	//closegraph();
	free(terrain.personnes);
	return 0;
}





