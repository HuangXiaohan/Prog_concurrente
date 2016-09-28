/*
 * monoThread.c
 *
 *  Created on: 28 sept. 2016
 *      Author: epu
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *execution(void *arg)
{
    printf("Nous sommes dans le thread.\n");

    /* Pour enlever le warning */
    (void) arg;
    pthread_exit(NULL);
}

int monoThread()
{
	pthread_t thread;

	printf("Execution du programme avec un unique thread.\n");

	if(pthread_create(&thread, NULL, execution, NULL) == -1) {
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

