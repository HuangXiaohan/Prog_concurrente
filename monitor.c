/*
 * monitor.c
 *
 *  Created on: 4 déc. 2016
 *      Author: epu
 */


//#include "myUtils.h"
#include "monitor.h"


void initialise_monitor(Monitor* monitor)
{
	pthread_mutex_init(&monitor->mut,NULL);
	pthread_cond_init(&monitor->cond,NULL);
	monitor->locked = 0;
}

void verrouille_monitor(Monitor* monitor){
	pthread_mutex_lock(&monitor->mut);

	if(monitor->locked) pthread_cond_wait(&monitor->cond, &monitor->mut);
	monitor->locked = 1;

	pthread_mutex_unlock(&monitor->mut);
}


void deverrouille_monitor(Monitor* monitor){
	pthread_mutex_lock(&monitor->mut);

	monitor->locked = 0;
	pthread_cond_signal(&monitor->cond);

	pthread_mutex_unlock(&monitor->mut);
}

void detruit_monitor(Monitor* monitor)
{
	pthread_mutex_destroy(&monitor->mut);
	pthread_cond_destroy(&monitor->cond);
}
