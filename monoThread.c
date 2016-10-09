/*
 * monoThread.c
 *
 *  Created on: 28 sept. 2016
 *      Author: Xiaohan Huang et Gaspard Lacroix
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "myUtils.h"
#include "deplacements.h"

void *executionT0(void* arg)
{
	Terrain* terrain = (Terrain*) arg;
	int oneAlive;

	do{
		oneAlive = 0;
	    for(int i=0; i < terrain->nbPersonnes; i++){
	    	if(terrain->personnes[i].alive){
	    		oneAlive =1;
	    		avancer(terrain, i);
	    	}
		}
	}while(oneAlive);

    pthread_exit(NULL);
}

int monoThread(Terrain* terrain)
{
	pthread_t thread;

	//printf("Execution du programme avec un unique thread.\n");

	if(pthread_create(&thread, NULL, executionT0, terrain) == -1) {
		perror("pthread_create");
		return EXIT_FAILURE;
	}

	if (pthread_join(thread, NULL)) {
		perror("pthread_join");
		return EXIT_FAILURE;
	}

	//printf("Fin d'execution.\n");

	return EXIT_SUCCESS;

}

