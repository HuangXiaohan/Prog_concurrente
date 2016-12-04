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

sem_t pixel[LARGEUR][LONGUEUR];

void *executionT1_e2(void* arg)
{
	pthread_detach(pthread_self());

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

					int sem_x = terrain->personnes[i].x, sem_y = terrain->personnes[i].y;
					int bord = (sem_x >= largeur*(numThread+1)-4 || (sem_x < largeur*numThread +4 && numThread != 0))? 1 : 0;

					if(bord){
						if(sem_y < LARGEUR/2){
							sem_x += 3;
						}else{
							sem_x += 3;
							sem_y -= 1;
						}

						sem_wait(&pixel[sem_y][sem_x]);
						for(int i=1 ; i < 4; i++){
							sem_wait(&pixel[sem_y][sem_x-i]);
							sem_wait(&pixel[sem_y+i][sem_x]);
						}
						for(int i=0 ; i < 4; i++){
							sem_wait(&pixel[sem_y+i][sem_x-4]);
							sem_wait(&pixel[sem_y+4][sem_x-i]);
						}
						sem_wait(&pixel[sem_y+4][sem_x-4]);
					}

					avancer(terrain, i);

					if(bord){
						sem_post(&pixel[sem_y][sem_x]);
						for(int i=1 ; i < 4; i++){
							sem_post(&pixel[sem_y][sem_x-i]);
							sem_post(&pixel[sem_y+i][sem_x]);
						}

						for(int i=0 ; i < 4; i++){
							sem_post(&pixel[sem_y+i][sem_x-4]);
							sem_post(&pixel[sem_y+4][sem_x-i]);
						}
						sem_post(&pixel[sem_y+4][sem_x-4]);
					}
				}
			}
		}
	}while(oneAlive);


	the_end[numThread] = 1;
	sem_post (&semaphore[numThread]);

	pthread_exit(NULL);
}

int quatreThreads_e2(Terrain* terrain){

	pthread_t threads[4];

	for(int i = 0; i < LARGEUR; i++)
		for(int j = 0; j < LONGUEUR; j++)
			sem_init(&pixel[i][j], 0, 1);

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

