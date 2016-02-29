/*
Matt Walz
CS 362-400
Assignment 2: Documentation of Smithy and Adventurer Cards and discardCard() and updateCoins() Methods


Smithy-----------------------------------------------------------
The ‘Smithy’ is an action card which enables the player of the card to draw three additional cards and add them to their current hand. This is done by calling drawCard()
three times. After drawing the three cards, Smithy calls discardCard() with the appropriate parameters to put Smithy in the played card pile.


Adventurer-----------------------------------------------------
The ‘Adventurer’ is an action card which enables the player of the card to draw cards from their deck until they have drawn two ‘treasure’ cards. These two ‘treasure’ cards
are then added to the players hand while all non-‘treasure’ cards drawn this way are discarded. The mechanism for doing this is a loop. As cards are drawn, if the card is a
non-‘treasure’ card it is put into a temporary hand of cards while if the drawn card is a ‘treasure’ card, then a loop control counter is incremented and the card is placed
in the player’s hand. Once the loop control counter reaches two, the player stops drawing cards and all cards currently in the temporary hand are put into the discard pile.
Additionally, if during the course of drawing cards the player’s deck is found empty when a card is supposed to be drawn, then the discard pile (this does not include the
current temporary hand) is shuffled and becomes the player’s deck. The card to be drawn is then taken from the newly replenished deck.


discardCard() ---------------------------------------------------
The discardCard() method takes a card from a player’s hand and places it either in the played cards pile or in the discard pile (this is determined by the trashFlag
variable). If successful, the played/discarded card is removed from the player’s hand and the game state variable for the player’s hand size is reduced by 1. Additionally,
the method returns 0 on success.

Parameters:
int handPos: position in player’s hand of card being played/discarded
int currentPlayer: id of player who played/discarded card
struct gameState *state: pointer to gameState struct being used by current game
int trashFlag: integer determining whether card is moved to played pile (<1) or discard pile (>=1)


updateCoins() ---------------------------------------------------
The updateCoins() method calculates the amount of treasure available for a player to purchase cards from the supply and updates the corresponding game state variable. This
calculation is made by adding 1 for every ‘copper’, 2 for every ‘silver’, and 3 for every ‘gold’ card present in the player’s current hand as well as adding all bonuses
accrued from cards played by the player during the current turn (e.g. playing a Festival would add 2 to the bonus total). Upon successful completion, the method returns 0.

Parameters:
int Player: id of player whose coins are being tallied
struct gameState *state: pointer to gameState struct being used by current game
int bonus: integer value equal to the total amount of bonus coins accrued from action cards played during the player’s current turn

*/