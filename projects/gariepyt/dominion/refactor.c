/*
Smithy: (incorrect)
	Made its own function: playSmithy(int currentPlayer, struct gameState *state, int handPos)
	Change flag from discardCard() from 0 to 1

Adventurer: (incorrect)
	Made its own function: playAdventurer(int drawntreasure, struct gameState *state, int currentPlayer, int cardDrawn, int * temphand, int z)
	discard should get tempHand[z-1], but instead is from z

Council_Room: (incorrect)
	Made its own function: playCouncil(struct gameState *state, int currentPlayer, int cardDrawn, int z, int handPos)
	For loop now has <= instead of <

Salvager: (incorrect)
	Made its own function: playSalvager(struct gameState *state, int choice1, int currentPlayer, int handPos)
	State of the coin is now subracted instead of added

Village: (correct)
	Made its own function: playVillage(int currentPlayer, struct gameState *state, int handPos)
	No additional changes
*/