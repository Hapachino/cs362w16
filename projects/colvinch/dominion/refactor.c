Smithy Card (incorrect):
    Made its own function: playSmithy(int currentPlayer, struct gameState *state, int handPos)
    Changed number of cards drawn to 2 instead of 3.

Adventurer Card (incorrect):
    Made its own function: playAdventurer(int drawntreasure, struct gameState *state, int currentPlayer, int cardDrawn, int * temphand, int z)
    Changed if statement to remove copper.

Village Card (incorrect):
    Made its own function: playVillage(int currentPlayer, struct gameState *state, int handPos)
    Change flag from discardCard() from 0 to 1.

Feast Card (incorrect):
    Made its own function: playFeast(struct gameState *state, int choice1, int currentPlayer, int handPos)
    Changed if statement for checking supplyCount such that if there is 1 or less cards left of card of choice,
    the player cannot purchase the card and the "None of that card left, sorry!" message is printed
    (i.e. if there is only one card left of its kind, the player cannot purchase it using Feast Card).

Council Room Card (correct):
    Made its own function: playCouncil_Room(struct gameState *state, int currentPlayer, int cardDrawn, int z, int handPos)
    No other changes.

