/*
 * quatreThreads.c
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

typedef struct{
	Terrain* terrain;
	int numThread;
} Arguments;

void executionT1(Terrain* terrain, int numThread)
{
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
}

void *executionT1_e1(void* arg)
{
	Arguments* arguments = (Arguments*) arg;
	Terrain* terrain = arguments->terrain;
	int numThread = arguments->numThread;
	free(arguments);

	executionT1(terrain, numThread);

	pthread_exit(NULL);
}

int quatreThreads_e1(Terrain* terrain)
{
	pthread_t threads[4];

	for(int i =0; i < 4; i++){
		Arguments* arguments = (Arguments*)malloc(sizeof(Arguments));
		arguments->terrain = terrain;
		arguments->numThread = i;

		if(pthread_create(&threads[i], NULL, executionT1_e1, arguments) == -1) {
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

	return EXIT_SUCCESS;

}


sem_t semaphore[4];
int the_end[4];


void *executionT1_e2(void* arg)
{
	pthread_detach(pthread_self());

	Arguments* arguments = (Arguments*) arg;
	Terrain* terrain = arguments->terrain;
	int numThread = arguments->numThread;
	free(arguments);

	executionT1(terrain, numThread);

	the_end[numThread] = 1;
	sem_post (&semaphore[numThread]);

	pthread_exit(NULL);
}

int quatreThreads_e2(Terrain* terrain){

	pthread_t threads[4];

	for(int i =0; i < 4; i++){
		the_end[i] = 0;
		sem_init(&semaphore[i], 0, 0);

		Arguments* arguments = (Arguments*)malloc(sizeof(Arguments));
		arguments->terrain = terrain;
		arguments->numThread = i;

		if(pthread_create(&threads[i], NULL, executionT1_e2, arguments) == -1) {
			perror("pthread_create");
			return EXIT_FAILURE;
		}
	}

	// Attente de la fin des thread
	for(int i =0; i < 4; i++){
		while (!the_end[i]) {
			sem_wait (&semaphore[i]);
		}
		sem_destroy(&semaphore[i]);
	}

	return EXIT_SUCCESS;
}

