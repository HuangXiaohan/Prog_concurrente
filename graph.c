/*
 * graph.c
 *
 *  Created on: 29 sept. 2016
 *      Author: Xiaohan Huang et Gaspard Lacroix
 */

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"


void dessinTerrain(Terrain *t){
	//int ch;
	//int gd = DETECT, gm = VGAMAX;
	//initgraph(&gd,&gm,0);

	//dessin un rectangle de terrain
	rectangle(DECALAGE,DECALAGE,LONGUEUR+DECALAGE,LARGEUR+DECALAGE);

	//dessin haut du mur de gauche
	rectangle(DECALAGE,DECALAGE,15+DECALAGE,59+DECALAGE);
	floodfill(60,100,4);

	//dessin Bbas du mur de gauche
	rectangle(DECALAGE,68+DECALAGE,15+DECALAGE,127+DECALAGE);
	floodfill(60,120,4);

	//dessin haut du mur de droite
	rectangle(112+DECALAGE,DECALAGE,127+DECALAGE,55+DECALAGE);
	floodfill(170,70,4);

	//dessin bas du mur de droite
	rectangle(112+DECALAGE,72+DECALAGE,127+DECALAGE,127+DECALAGE);
	floodfill(170,130,4);

	//dessin les personnes
	for(int i=0; i < t->nbPersonnes; i++){
		setcolor(RED);
		rectangle(t->personnes[i].x + DECALAGE, t->personnes[i].y + DECALAGE, t->personnes[i].x + DECALAGE+3, t->personnes[i].y + DECALAGE+3);
	}

	//closegraph();
}

void updatePosPersonne(int prevx, int prevy, int newx, int newy){
	setcolor(BLACK);
	rectangle(prevx + DECALAGE, prevy + DECALAGE, prevx + DECALAGE+3, prevy + DECALAGE+3);

	setcolor(RED);
	rectangle(newx + DECALAGE, newy + DECALAGE, newx + DECALAGE+3, newy + DECALAGE+3);
}



