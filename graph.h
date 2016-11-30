/*
 * graph.h
 *
 *  Created on: 29 sept. 2016
 *      Author: Xiaohan Huang et Gaspard Lacroix
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "graphics.h"
#include "myUtils.h"

#define DECALAGE 50

void dessinTerrain(Terrain *t);

void updatePosPersonne(int prevx, int prevy, int newx, int newy);

#endif /* GRAPH_H_*/
