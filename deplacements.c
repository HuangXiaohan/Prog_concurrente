/*
 * deplacements.c
 *
 *  Created on: 29 sept. 2016
 *      Author: epu
 */

#include "myUtils.h"
#include <math.h>

#define NORD 1
#define NORD_OUEST 2
#define OUEST 3
#define SUD_OUEST 4
#define SUD 5



void avancer(Terrain* terrain, int numPersonne){

	double directions[3][2] = {{-1, -1, -1},{-1, -1, -1}};

	int centreX = terrain->personnes[numPersonne].x +2;
	int centreY = terrain->personnes[numPersonne].y +2;

	if(terrain->personnes[numPersonne].y < 64){
		double distance = sqrt( pow((centreX+10),2) + pow((centreY+1-63),2) );
		directions[0][1] = SUD;
		directions[0][0] = distance;

		distance = sqrt( pow((centreX-1+10),2) + pow((centreY+1-63),2) );
		directions[1][1] = SUD_OUEST;
		directions[1][0] = distance;
	}
	else{
		double distance = sqrt( pow((centreX+10),2) + pow((centreY-1-63),2) );
		directions[0][1] = NORD;
		directions[0][0] = distance;

		distance = sqrt( pow((centreX-1+10),2) + pow((centreY-1-63),2) );
		directions[1][1] = NORD_OUEST;
		directions[1][0] = distance;
	}

	double distance = sqrt( pow((centreX-1+10),2) + pow((centreY-63),2) );
	directions[2][1] = OUEST;
	directions[2][0] = distance;

	ordonner(directions);



}


int checkFree(Terrain terrain, Personne* p, int direction){
	switch(direction){

	case SUD:
		for(int i=0; i < 4; i++)
			if(terrain->surface[p->x+i][p->y+4] != -1)
				return 0;
		break;

	case SUD_OUEST:
		for(int i=0; i < 3; i++)
			if(terrain->surface[p->x-1][p->y+1+i] != -1)
				return 0;
		for(int i=0; i < 4; i++)
			if(terrain->surface[p->x-1+i][p->y+4] != -1)
				return 0;
		break;

	case NORD:
		for(int i=0; i < 4; i++)
			if(terrain->surface[p->x+i][p->y-1] != -1)
				return 0;
		break;

	case NORD_OUEST:
		for(int i=0; i < 3; i++)
			if(terrain->surface[p->x-1][p->y+i] != -1)
				return 0;
		for(int i=0; i < 4; i++)
			if(terrain->surface[p->x-1+i][p->y-1] != -1)
				return 0;
		break;
	}
	case OUEST:
		for(int i=0; i < 4; i++)
			if(terrain->surface[p->x-1][p->y+i] != -1)
				return 0;
}


void ordonner(double directions[3][2]){
	if(directions[1][0] < directions[0][0])
		swap(directions, 0, 1);
	if(directions[2][0] < directions[1][0])
		swap(directions, 2, 1);
	if(directions[1][0] < directions[0][0])
		swap(directions, 0, 1);
}


void swap(double directions[3][2], int ligne1, int ligne2){
	double temp0 = directions[ligne1][0];
	double temp1 = directions[ligne1][1];
	directions[ligne1][0] = directions[ligne2][0];
	directions[ligne1][1] = directions[ligne2][1];
	directions[ligne2][0] = temp0;
	directions[ligne2][1] = temp1;
}
