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
//Refactored functions
int playAdventurer(int currentPlayer, struct gameState *state);
int playSmithy(int currentPlayer, struct gameState *state, int handPos);
int playCouncil_room(int currentPlayer, struct gameState *state, int handPos);
int playMine(int currentPlayer, struct gameState *state, int handPos,
            int choice1, int choice2);
int playRemodel(int currentPlayer, struct gameState *state, int handPos,
            int choice1, int choice2);
//End refactored functions

#endif
