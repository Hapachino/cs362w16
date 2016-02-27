/*
Jeannine Amm
CS362w16
Assignment2: refactor.c

Instructions: Pick five cards implemented in dominion.c.  Choose 3 cards of your
choice and smithy and adventurer cards are mandatory.  Refactor the code so that
 these cards are implemented in their own functions, rather than as part of the
 switch statement in cardEffect.  You should call the functions for these cards
 in the appropriate place in cardEffect.  Your implementation of at least 4 of
 these 5 cards should be incorrect in some way, i.e. introduce subtle bugs that
 are hard to catch in your changes.

Program structure Changes:
	New header file created dominion_cards.h with the following card function declarations:
		int playSmithy(int handPos, struct gameState *state);
		int playAdventurer(struct gameState *state);
		int playEmbargo(int choice1, int handPos, struct gameState *state);
		int playAmbassador(int choice1, int choice2, int handPos,
				struct gameState *state);
		int playSteward(int choice1, int choice2, int choice3, int handPos,
				struct gameState *state);
	Removed any playCard declarations from dominion.h

Refactored Functions and function calls:

	playAdventurer function refactor contained in dominion.c:
		cardEffect() changes:
			- code under switch smithy moved to playAdventurer().
			- function called from switch smithy using return playAdventurer();.
		moved from cardEffect declarations into function:
			- int z, cardDrawn, drawntreasure;
			- int temphand[MAX_HAND];
		additional statements added to function playAdventurer():
			- int player = whoseTurn(state);

	playSmithy function refactor contained in dominion.c:
		cardEffect() changes:
			- code under switch smithy moved to playSmithy
			- function called from switch smithy using return playSmithy();.
		additional statements added to function playSmithy():
			- int i;
			- int player = whoseTurn(state);

	playEmbargo function refactor contained in dominion.c:
		cardEffect() changes:
			function called from switch embargo using return playEmbargo();.
		additional statements added to function:
			int player = whoseTurn(state);

	playAmbassador function refactor contained in dominion.c:
		cardEffect() changes:
			- function called from switch ambassador using return playAmbassador();.
		additional statements added to function:
			- int j = 0;
			- int i;
			- int player = whoseTurn(state);

	playSteward function refactor contained in dominion.c:
		cardEffect() changes:
			- function called from switch steward using return playSteward();.
		additional statements added to function:
			- int player = whoseTurn(state);

Bugs Introduced:
Adventurer: Add z--; before cards in tempHand discarded.  Should discard one less
	card.
playSmithy: added updateCoins(player, state, 1) to add a coin;
Ambassador: Changed toFlag in call to GainCard to 2.  Should add card to hand
	instead of discard pile.
Steward: Set trashFlag to 1 in call to discardCard()

*/
