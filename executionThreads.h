/*
 * executionThreads.h
 *
 *  Created on: 29 sept. 2016
 *      Author: epu
 */

#ifndef EXECUTIONTHREADS_H_
#define EXECUTIONTHREADS_H_

#include "myUtils.h"

int monoThread(Terrain* terrain);
void multiThread(Terrain* terrain);

int quatreThreads(Terrain* terrain);


#endif /* EXECUTIONTHREADS_H_ */
