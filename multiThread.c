/*
 * multiThread.c
 *
 *  Created on: 6 oct. 2016
 *      Author: Xiaohan Huang et Gaspard Lacroix
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "myUtils.h"
#include "deplacements.h"


typedef struct Args{
	Terrain* terrain;
	int personNb;
}Args;

void *multi_execution_e1(void* arg){
	Args* args = (Args*) arg;
	Terrain* terrain = args->terrain;
	int pnb = args->personNb;
	free(args);

	while(terrain->personnes[pnb].alive)
		avancer(terrain, pnb);

    pthread_exit(NULL);
}


int multiThread_e1(Terrain* terrain){
	pthread_t thread[terrain->nbPersonnes];
	Args *args[terrain->nbPersonnes];


	for(int i = 0; i < terrain->nbPersonnes; i++){
		args[i] = malloc(sizeof(Args));
		args[i]->terrain = terrain;
		args[i]->personNb = i;

		if(pthread_create(&thread[i], NULL, multi_execution_e1, args[i]) == -1) {
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

	return EXIT_SUCCESS;
}

static sem_t* semaphore;
static int* the_end;


void *multi_execution_e2(void* arg){
	Args* args = (Args*) arg;
	Terrain* terrain = args->terrain;
	int pnb = args->personNb;
	free(args);

	while(terrain->personnes[pnb].alive)
		avancer(terrain, pnb);

	the_end[pnb] = 1;
	sem_post (&semaphore[pnb]);

    pthread_exit(NULL);
}

int multiThread_e2(Terrain* terrain){
	pthread_t thread[terrain->nbPersonnes];
	Args *args[terrain->nbPersonnes];

	semaphore = (sem_t*)malloc(sizeof(sem_t) * terrain->nbPersonnes);
	the_end = (int*) malloc(sizeof(int) * terrain->nbPersonnes);


	for(int i = 0; i < terrain->nbPersonnes; i++){
		the_end[i] = 0;
		sem_init(&semaphore[i], 0, 0);

		args[i] = malloc(sizeof(Args));
		args[i]->terrain = terrain;
		args[i]->personNb = i;

		if(pthread_create(&thread[i], NULL, multi_execution_e2, args[i]) == -1) {
			perror("pthread_create");
			return EXIT_FAILURE;
		}
	}

	// Attente de la fin des thread
	for(int i =0; i < terrain->nbPersonnes; i++){
		while (!the_end[i]) {
			sem_wait (&semaphore[i]);
		}
		sem_destroy(&semaphore[i]);
	}


	return EXIT_SUCCESS;
}





