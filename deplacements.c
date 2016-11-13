/*
 * deplacements.c
 *
 *  Created on: 29 sept. 2016
 *      Author: Xiaohan Huang et Gaspard Lacroix
 */

#include <math.h>
#include <stdio.h>

#include "myUtils.h"

#define NORD 1
#define NORD_OUEST 2
#define OUEST 3
#define SUD_OUEST 4
#define SUD 5



void swap(double directions[3][2], int ligne1, int ligne2){
	double temp0 = directions[ligne1][0];
	double temp1 = directions[ligne1][1];
	directions[ligne1][0] = directions[ligne2][0];
	directions[ligne1][1] = directions[ligne2][1];
	directions[ligne2][0] = temp0;
	directions[ligne2][1] = temp1;
}

void ordonner(double directions[3][2]){
	if(directions[1][0] < directions[0][0])
		swap(directions, 0, 1);
	if(directions[2][0] < directions[1][0])
		swap(directions, 2, 1);
	if(directions[1][0] < directions[0][0])
		swap(directions, 0, 1);
}


int checkFree(Terrain* terrain, Personne* p, int direction){
	if(p->x == 0) return 1;

	switch(direction){

	case SUD:
		for(int i=0; i < 4; i++)
			if(terrain->surface[p->y+4][p->x+i] != -1)
				return 0;
		break;

	case SUD_OUEST:
		for(int i=0; i < 3; i++)
			if(terrain->surface[p->y+1+i][p->x-1] != -1)
				return 0;
		for(int i=0; i < 4; i++)
			if(terrain->surface[p->y+4][p->x-1+i] != -1)
				return 0;
		break;

	case NORD:
		for(int i=0; i < 4; i++)
			if(terrain->surface[p->y-1][p->x+i] != -1)
				return 0;
		break;

	case NORD_OUEST:
		for(int i=0; i < 3; i++)
			if(terrain->surface[p->y+i][p->x-1] != -1)
				return 0;
		for(int i=0; i < 4; i++)
			if(terrain->surface[p->y-1][p->x-1+i] != -1)
				return 0;
		break;

	case OUEST:
		for(int i=0; i < 4; i++)
			if(terrain->surface[p->y+i][p->x-1] != -1)
				return 0;
		break;
	}

	return 1;

}

void deplacer(Terrain* terrain, int numPersonne, int direction){

	Personne* p = &(terrain->personnes[numPersonne]);

	switch(direction){

	case SUD:
		for(int i=0; i < 4; i++){
			terrain->surface[p->y][p->x+i] = -1;
			terrain->surface[p->y+4][p->x+i] = numPersonne;
		}
		p->y++;

		break;

	case SUD_OUEST:
		for(int i=0; i < 3; i++){
			terrain->surface[p->y+1+i][p->x+3] = -1;
			terrain->surface[p->y+1+i][p->x-1] = numPersonne;

		}
		for(int i=0; i < 4; i++){
			terrain->surface[p->y][p->x+i] = -1;
			terrain->surface[p->y+4][p->x-1+i] = numPersonne;
		}
		p->x--;
		p->y++;
		break;

	case NORD:
		for(int i=0; i < 4; i++){
			terrain->surface[p->y+3][p->x+i] = -1;
			terrain->surface[p->y-1][p->x+i] = numPersonne;
		}
		p->y--;
		break;

	case NORD_OUEST:
		for(int i=0; i < 3; i++){
			terrain->surface[p->y+i][p->x+3] = -1;
			terrain->surface[p->y+i][p->x-1] = numPersonne;

		}
		for(int i=0; i < 4; i++){
			terrain->surface[p->y+3][p->x+i] = -1;
			terrain->surface[p->y-1][p->x-1+i] = numPersonne;
		}
		p->x--;
		p->y--;
		break;

	case OUEST:
		for(int i=0; i < 4; i++){
			terrain->surface[p->y+i][p->x+3] = -1;
			terrain->surface[p->y+i][p->x-1] = numPersonne;
		}
		p->x--;
		break;
	}

	if(p->x == 0){
		p->alive = 0;
		for(int i=0; i < 4; i++)
			for(int j=0; j < 4; j++)
				terrain->surface[p->y+j][p->x+i] = -1;

		//printf("Personne %d est sortie\n", numPersonne);
	}
}



void avancer(Terrain* terrain, int numPersonne){

	double directions[3][2];
	for(int i =0; i < 3*2; i++){
		directions[0][i] = -1;
	}

	int centreX = terrain->personnes[numPersonne].x +2;
	int centreY = terrain->personnes[numPersonne].y +2;

	if(centreY <= LARGEUR/2){
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

	int current = 0;

	for(current =0; current < 3; current++){
		if( checkFree(terrain, &(terrain->personnes[numPersonne]), directions[current][1]) )
			break;
	}

	if(current != 3)
		deplacer(terrain, numPersonne, directions[current][1]);


}



