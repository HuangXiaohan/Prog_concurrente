/*
 * executionThreads.h
 *
 *  Created on: 29 sept. 2016
 *      Author: Xiaohan Huang et Gaspard Lacroix
 */

#ifndef EXECUTIONTHREADS_H_
#define EXECUTIONTHREADS_H_

#include "myUtils.h"

int monoThread_e1(Terrain* terrain);
int quatreThreads_e1(Terrain* terrain);
int multiThread_e1(Terrain* terrain);

int monoThread_e2(Terrain* terrain);
int quatreThreads_e2(Terrain* terrain);
int multiThread_e2(Terrain* terrain);

//int monoThread_e3(Terrain* terrain);
int quatreThreads_e3(Terrain* terrain);
int multiThread_e3(Terrain* terrain);


#endif /* EXECUTIONTHREADS_H_ */
