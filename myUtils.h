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

typedef struct Terrain{
	int surface[LARGEUR][LONGUEUR];
	int nbPersonnes;
}Terrain;



#endif /* MYUTILS_H_ */
