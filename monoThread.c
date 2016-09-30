/*
 * monoThread.c
 *
 *  Created on: 28 sept. 2016
 *      Author: epu
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "myUtils.h"

void *execution(Terrain* terrain)
{
    printf("Nous sommes dans le thread.\n");

    for(int i=0; i < terrain->nbPersonnes; i++){
    	printf("P%d : %d,%d\n", i, terrain->personnes[i].x, terrain->personnes[i].y);
    }

    pthread_exit(NULL);
}

int monoThread(Terrain* terrain)
{
	pthread_t thread;

	printf("Execution du programme avec un unique thread.\n");

	if(pthread_create(&thread, NULL, execution, terrain) == -1) {
		perror("pthread_create");
		return EXIT_FAILURE;
	}

	if (pthread_join(thread, NULL)) {
		perror("pthread_join");
		return EXIT_FAILURE;
	}

	printf("Fin d'execution.\n");

	return EXIT_SUCCESS;

}
