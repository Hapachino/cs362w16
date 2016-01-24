Smithy 
This card allows the current player to draw three cards from his deck. If the number of cards in the deck is less than the 
number of cards to be drawn, you must shuffle the discard pile into the deck. There is a function cardEffect(), and when 
"smithy" is passed in as an argument, the drawCard() function is called three times. Finally, the discardCard() function 
is called to discard the smithy card that was just played.

Adventurer
When "adventurer" is passed as an argument into the function cardEffect(), the player reveals cards from his deck 
until he reveals two Treasure cards. He puts those Treasure cards in his hand and discards the other revealed cards. 
The non-Treasure cards should probably stored into a temporary array. There should be a counter to keep track of the 
number of Treasure cards drawn (which should be two maximum).Once again, if the deck is empty you must shuffle the 
discard pile into the deck.

discardCard()
This method handles the action of discarding a card after it has been played. It has a trashFlag set to check whether
or not the card should be placed in the trash pile. It also uses an int to keep track of the current player. It has no 
dependencies and does not use any data structures. The input is a player, card position, and state. 

updateCoins()
This method is called in the Game start functions, Play a card functions, and End turn functions. It returns
the number of a specific card that you own in total (including the number in your hand and discard deck). It uses data
structure int i, which serves as an index counter.
