/*
Josh Homann
CS362 Q1 2016
Assignment 2

Smithy:  This is an action card with a cost of 4.  When played the player draws 3 cards.

Adventurer:  This is an action card with a cost of 6.  When played the player draws a card.  If the drawn card is a treasure it is placed in the players hand, otherwise it is discarded.  The draw is repeated until two treasure
cards are drawn.


discardCard():  This function is used to remove a card from a players hand.  Rather confusingly it can be used to discard a card or trash a card.
int discardCard(int handPos, int currentPlayer, struct gameState *state, int trashFlag)
Parameters:
1) int handPos : The position of the card in the player's hand
2) int currentPlayer : The index of player's hand to be modified
3) struct gameState *state : A pointer to the game state struct, which is a singleton representing the current state of the game.  The hand and handcount of this struct are potentially modified.
4) int trashFlag : 0 indicates the card is discarded and reshuffled into the players deck.  1 indicates the card is trashed and removed from the player's deck


updateCoins() This function updates the number of coins that a player has based on the cards in the players hands and the value supplied in the bonus field.
int updateCoins(int player, struct gameState *state, int bonus)
Parameters:
1) int player : The index of the player to update
2) struct gameState *state : A pointer to the game state struct, which is a singleton representing the current state of the game.  The coins property of this struct is modified.  The hand property of the struct is iterated through and read to determine how many coins to add.
3) int bonus : The number of bonus coins to add in addition to what is in the player's hand
*/
