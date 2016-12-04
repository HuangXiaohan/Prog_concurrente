/*
 * monitor.h
 *
 *  Created on: 4 déc. 2016
 *      Author: epu
 */

#ifndef MONITOR_H_
#define MONITOR_H_

#include <pthread.h>
#include <semaphore.h>

typedef struct{
	pthread_mutex_t mut;
	pthread_cond_t cond;
	int locked;
} Monitor;


void initialise_monitor(Monitor* monitor);
void verrouille_monitor(Monitor* monitor);
void deverrouille_monitor(Monitor* monitor);
void detruit_monitor(Monitor* monitor);


#endif /* MONITOR_H_ */
