/*
 * quatreThreads.c
 *
 *  Created on: 6 oct. 2016
 *      Author: epu
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "myUtils.h"
#include "deplacements.h"

typedef struct{
	Terrain* terrain;
	int numThread;
} Arguments;

void *executionT1(void* arg)
{
	Arguments* arguments = (Arguments*) arg;
	Terrain* terrain = arguments->terrain;
	int numThread = arguments->numThread;
	free(arguments);
	int largeur = LONGUEUR/4;
	int oneAlive;

	do{
		oneAlive = 0;
	    for(int i=0; i < terrain->nbPersonnes; i++){
	    	if(terrain->personnes[i].alive && terrain->personnes[i].x >= largeur*numThread){
	    		oneAlive =1;

	    		if(terrain->personnes[i].x < largeur*(numThread+1)){
	    			avancer(terrain, i);
	    		}
	    	}
		}
	}while(oneAlive);

    pthread_exit(NULL);
}

int quatreThreads(Terrain* terrain)
{
	pthread_t threads[4];

	//printf("Execution du programme avec le terrain partage en 4 threads.\n");

	for(int i =0; i < 4; i++){
		Arguments* arguments = (Arguments*)malloc(sizeof(Arguments));
		arguments->terrain = terrain;
		arguments->numThread = i;

		if(pthread_create(&threads[i], NULL, executionT1, arguments) == -1) {
			perror("pthread_create");
			return EXIT_FAILURE;
		}
	}

	for(int i =0; i < 4; i++){
		if (pthread_join(threads[i], NULL)) {
			perror("pthread_join");
			return EXIT_FAILURE;
		}
	}

	//printf("Fin d'execution.\n");

	return EXIT_SUCCESS;

}

