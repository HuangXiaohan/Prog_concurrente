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
#include <sched.h>
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

sem_t* semaphore;
int* the_end;

sem_t pixel[LARGEUR][LONGUEUR];


void *multi_execution_e2(void* arg){
	pthread_detach(pthread_self());

	Args* args = (Args*) arg;
	Terrain* terrain = args->terrain;
	int pnb = args->personNb;
	free(args);

	while(terrain->personnes[pnb].alive){
		sched_yield();

		//printf("%d : %d,%d\n", pnb, terrain->personnes[pnb].x, terrain->personnes[pnb].y);

		int sem_x = terrain->personnes[pnb].x, sem_y = terrain->personnes[pnb].y, delta;
		int  milieu = (sem_y >= (LARGEUR/2) -4 && sem_y < (LARGEUR/2) +4)? 1 : 0;

		if(terrain->personnes[pnb].y < LARGEUR/2){
			sem_x += 3;
			delta = 1;
		}else{
			sem_x += 3;
			sem_y += 3;
			delta = -1;
		}

		sem_wait(&pixel[sem_y][sem_x]);
		for(int i=1 ; i < 4; i++){
			sem_wait(&pixel[sem_y][sem_x-i]);
			sem_wait(&pixel[sem_y+i*delta][sem_x]);
		}
		for(int i=0 ; i < 4; i++){
			sem_wait(&pixel[sem_y+i*delta][sem_x-4]);
			if(!milieu) sem_wait(&pixel[sem_y+4*delta][sem_x-i]);
		}
		if(!milieu) sem_wait(&pixel[sem_y+4*delta][sem_x-4]);


		avancer(terrain, pnb);

		sem_post(&pixel[sem_y][sem_x]);
		for(int i=1 ; i < 4; i++){
			sem_post(&pixel[sem_y][sem_x-i]);
			sem_post(&pixel[sem_y+i*delta][sem_x]);
		}

		for(int i=0 ; i < 4; i++){
			sem_post(&pixel[sem_y+i*delta][sem_x-4]);
			if(!milieu) sem_post(&pixel[sem_y+4*delta][sem_x-i]);
		}
		if(!milieu) sem_post(&pixel[sem_y+4*delta][sem_x-4]);

	}
	/*
	printf("%d fini\n", pnb);
	for(int i =0; i < 8; i++){
		for(int j = 0; j < 16; j++){
			//sem_getvalue(&pixel[60+i][j], &n);
			printf("%d,", terrain->surface[60+i][j]);
		}
		printf("\n");
	}*/


	the_end[pnb] = 1;
	sem_post (&semaphore[pnb]);

	pthread_exit(NULL);
}

int multiThread_e2(Terrain* terrain){
	pthread_t thread[terrain->nbPersonnes];
	Args *args[terrain->nbPersonnes];

	semaphore = (sem_t*)malloc(sizeof(sem_t) * terrain->nbPersonnes);
	the_end = (int*) malloc(sizeof(int) * terrain->nbPersonnes);


	for(int i = 0; i < LARGEUR; i++)
		for(int j = 0; j < LONGUEUR; j++)
			sem_init(&pixel[i][j], 0, 1);


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

	for(int i = 0; i < LARGEUR; i++)
		for(int j = 0; j < LONGUEUR; j++)
			sem_destroy(&pixel[i][j]);

	free(semaphore);
	free(the_end);
	printf("Fini\n");

	return EXIT_SUCCESS;
}

