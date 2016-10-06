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

typedef struct Personne{
	// Les coordonnées sont celles du point en haut à gauche (0,0) de la personne
	int x;
	int y;
	int alive; // Est ce que la personne est sortie du terrain ou pas
}Personne;


typedef struct Terrain{
	int surface[LARGEUR][LONGUEUR];
	int nbPersonnes;
	Personne* personnes;
}Terrain;


void initialiserTerrain(Terrain *terrain);
void getPosition(int positions[]);
int initCheckfree(Terrain *terrain,int *p);

#endif /* MYUTILS_H_ */
