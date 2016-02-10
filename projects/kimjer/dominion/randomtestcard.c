/*
todo: figure out how to pass in by address in initI
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dominion.h"
#include "rngs.h"
#define YES 1
#define NO 0 
#define NUMCARDS 10

int isUnique(int k[]) {
	int i, j;
	for(i = 0; i < NUMCARDS; i++)
	{
		for(j = 1; j < NUMCARDS; j++)
		{
			if(j!=i && k[i] == k[j])
				return NO;	
		}	
	}
	return YES;
}

void makeK(int k[])
{
	int i;
	for(i = 0; i < NUMCARDS; i++)
	{
		k[i] = rand()%NUMCARDS;
	}
}	

void initI(struct infosStruct infos) 
{
	infos.i = 10;
	printf("the address of infos is %d\n", &infos);
}

int main() {
	srand(time(NULL));
	int i, j;
	puts("yo");
	struct gameState *g;
	g = newGame();
	int k[NUMCARDS]; 
		 
	do 
	{
		makeK(k);
	}
	while(!isUnique(k));
	
	for(i=0; i < NUMCARDS; i++)
		printf("%d, ", k[i]);
	printf("\n");
	struct infosStruct infos;
	initializeGame(2, k, 3, g);	
	printf("the address of infos is %d\n", &infos);
	initI(&infos);	
	printf("i is %d\n", infos.i);
	return 0; 
}
