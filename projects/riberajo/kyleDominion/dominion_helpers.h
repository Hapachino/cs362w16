#ifndef _DOMINION_HELPERS_H
#define _DOMINION_HELPERS_H

#include "dominion.h"

int drawCard(int player, struct gameState *state);
int updateCoins(int player, struct gameState *state, int bonus);
int discardCard(int handPos, int currentPlayer, struct gameState *state, 
		int trashFlag);
int gainCard(int supplyPos, struct gameState *state, int toFlag, int player);
int getCost(int cardNumber);
int cardEffect(int card, int choice1, int choice2, int choice3, 
	       struct gameState *state, int handPos, int *bonus);

//functions added for cardEffects, HW-2 1/14/16
//int smithyCard();
int adventurerCard(struct gameState *state, int currentPlayer);
int smithyCard(struct gameState *state, int currentPlayer, int handPos);
int villageCard(struct gameState *state, int currentPlayer, int handPos);
int greatHallCard(struct gameState *state, int currentPlayer, int handPos);
int outpostCard(struct gameState *state, int currentPlayer, int handPos);


#endif
