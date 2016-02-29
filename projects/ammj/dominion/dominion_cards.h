/*
 * dominion_cards.h
 *
 *  Created on: Jan 13, 2016
 *      Author: jamm8888
 */

#ifndef DOMINION_CARDS_H_
#define DOMINION_CARDS_H_

int playSmithy(int handPos, struct gameState *state);
int playAdventurer(struct gameState *state, int handPos);
int playEmbargo(int choice1, int handPos, struct gameState *state);
int playAmbassador(int choice1, int choice2, int handPos,
		struct gameState *state);
int playSteward(int choice1, int choice2, int choice3, int handPos,
		struct gameState *state);

#endif /* DOMINION_CARDS_H_ */
