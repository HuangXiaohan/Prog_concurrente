/*
 * multiThread.c
 *
 *  Created on: 6 oct. 2016
 *      Author: huang
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "myUtils.h"
#include "deplacements.h"


typedef struct Args{
	Terrain* terrain;
	int personNb;
}Args;

void *multi_execution(void* arg){
	Args* args = (Args*) arg;
	Terrain* terrain = args->terrain;
	int oneAlive;
	int pnb = args->personNb;
	//int i = 0;


	do{
		oneAlive = 0;
	    if(terrain->personnes[pnb].alive){
	    	oneAlive =1;
	    	avancer(terrain, pnb);
	    }
	    //printf("%d person %d\n",pnb,i++);
	}while(oneAlive);

    pthread_exit(NULL);
}


int multiThread(Terrain* terrain){
	pthread_t thread[terrain->nbPersonnes];
	Args *args[terrain->nbPersonnes];

	for(int i = 0; i < terrain->nbPersonnes; i++){
		args[i] = malloc(sizeof(Args));
		args[i]->terrain = terrain;
		args[i]->personNb = i;
	}

	for(int i = 0; i < terrain->nbPersonnes; i++){
		if(pthread_create(&thread[i], NULL, multi_execution, args[i]) == -1) {
			perror("pthread_create");
			return EXIT_FAILURE;
		}
	}

	for(int i = 0; i < terrain->nbPersonnes; i++){
		if (pthread_join(thread[i], NULL)) {
			perror("pthread_join");
			return EXIT_FAILURE;
		}
	}

	printf("Fin de multi execution.\n");

	return EXIT_SUCCESS;
}






