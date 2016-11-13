/*
 * monoThread.c
 *
 *  Created on: 28 sept. 2016
 *      Author: Xiaohan Huang et Gaspard Lacroix
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "myUtils.h"
#include "deplacements.h"

void executionT0(Terrain* terrain)
{
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
}

void *executionT0_e1(void* arg)
{
	Terrain* terrain = (Terrain*) arg;

	executionT0(terrain);

    pthread_exit(NULL);
}

int monoThread_e1(Terrain* terrain)
{
	pthread_t thread;

	if(pthread_create(&thread, NULL, executionT0_e1, terrain) == -1) {
		perror("pthread_create");
		return EXIT_FAILURE;
	}

	if (pthread_join(thread, NULL)) {
		perror("pthread_join");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;

}



sem_t semaphore;
int the_end;


void *executionT0_e2(void* arg)
{
	pthread_detach(pthread_self());

	Terrain* terrain = (Terrain*) arg;

	executionT0(terrain);

	the_end = 1;
	sem_post (&semaphore);

    pthread_exit(NULL);
}

int monoThread_e2(Terrain* terrain){

	pthread_t thread;

	the_end = 0;
	sem_init(&semaphore, 0, 0);

	if(pthread_create(&thread, NULL, executionT0_e2, terrain) == -1) {
		perror("pthread_create");
		return EXIT_FAILURE;
	}

	// Attente de la fin du thread
	while (!the_end) {
		sem_wait (&semaphore);
	}
	sem_destroy(&semaphore);


	return EXIT_SUCCESS;
}

