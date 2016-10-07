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
	int pnb = args->personNb;
	free(args);

	while(terrain->personnes[pnb].alive)
		avancer(terrain, pnb);

    pthread_exit(NULL);
}


int multiThread(Terrain* terrain){
	pthread_t thread[terrain->nbPersonnes];
	Args *args[terrain->nbPersonnes];


	printf("Execution du programme avec un thread pour chaque personne.\n");

	for(int i = 0; i < terrain->nbPersonnes; i++){
		args[i] = malloc(sizeof(Args));
		args[i]->terrain = terrain;
		args[i]->personNb = i;

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






