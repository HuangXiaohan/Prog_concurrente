/*
 * timeCalcule.c
 *
 *  Created on: 7 oct. 2016
 *      Author: huang
 */
#include <time.h>
#include "timeCalcule.h"

void detectTime(double t1[5], double t2[3]){
	int min = 0;
	int max = 0;
	int j = 0;
	for(int i = 1; i < 5; i++){
		if(t1[i] < t1[min])
			min = i;
		else if(t1[i] > t1[max])
			max = i;
	}
	for(int i = 0; i < 5; i++){
		if(i != min && i != max){
			t2[j++] = t1[i];
		}
	}
}

double calculeTime(double t[3]){
	double sum = 0;
	double avrg;
	for(int i = 0; i < 3; i++){
		sum += t[i];
	}
	avrg = sum/3;
	return avrg;
}

