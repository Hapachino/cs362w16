#Megan Fanning
#Documentation
#note: although is is uploaded as a .c file this is documentation and not code

#Smithy Card
The Smithy card is a action card which allows the user to draw and additional 3 cards from his or her deck using the drawCard method.
The initial cost of the Smithy card is 4 gold.

#Adventurer Card
This card has an initial cost of 6 gold required to add this card to the players deck.
The function of the Adventurer card allows the user to draw cards repeatedly until two treasure cards (Copper, Silver or Gold coins) are drawn. The user then discards all other cards drawn and places the two treasure cards in their hand.


#DiscardCard function
accepts the handPos,currentPlayer, gameState, and the trash flag.
if the card isn't trashed the played cards pile is incremented.
for both trashed and non-trashed cards the card is removed from the players hand by subracting once count of the card from the players hand and then reducing the players hand size.

#updateCoins function
This function accepts a player, gamestate and a bonus integer.
First the function clears the current state of the players coins setting them to 0 then it loops over the players hand and adds treature cards saving it to state->coin for the player. For each copper 1 is added, silver 2, gold three. Once these are summed the players bonus coins are added to their coins.

