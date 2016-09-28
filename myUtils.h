/*
 * myUtils.h
 *
 *  Created on: 22 sept. 2016
 *      Author: epu
 */

#ifndef MYUTILS_H_
#define MYUTILS_H_



#define LONGUEUR 512
#define LARGEUR 128
#define DECALAGE 50

typedef struct Terrain{
	int surface[LARGEUR][LONGUEUR];
	int nbPersonnes;
}Terrain;

void initialiserTerrain(Terrain *terrain);
int* getPosition();
int checkfree(Terrain *terrain,int *p);

#endif /* MYUTILS_H_ */
