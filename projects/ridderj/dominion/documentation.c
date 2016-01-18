Adventurer Card
----------------
The adventurer card is an action card. The cost of it is six
coins. It allows you to reveal cards from your deck until two
treasure cards arise. Those cards can be added to your hand and
the other cards taken from you deck should be discarded.

Adventurer card is called within a switch statement within the
cardEffect() function. The function keeps on looping until 2
treasure cards are found. If the current players deck count is
less then 1, the deck is shuffled. drawCard() is called once
everytime thru the loop and if it equals any type of coin, the
variable drawntreasure is increamented by one. If the card drawn
doesn't equal a coin it is stored in an array called temphand.
When all treasure cards have been found, another while loop uses
temphand to discard all cards in play that have been drawn.

Smithy Card
----------------
Smithy Card is an action card. The cost of it is four coins. Once
used, it allows the player to draw 3 cards for their deck and use
them in their hand.

Smithy card is called within a switch statement within the
cardEffect() function. While running it calls drawCard() three times
in a loop statement. drawCard() adds one card to the current players
hand everytime it is called. Once the action is completed it calls
discardCard() to remove it from the hand.

discardCard() Function
-----------------------
If trashFlag is less then one, puts used card into played pile. Using
the arguments handPos and currentPlayer it sets the gameState hand to -1,
to show a card isn't there. It then removes the card from the player's
hand by checking if the card is last card, the only one in the hand, or
replace discarded card with last card in hand. Each one of these actions
is followed by the gameState->handCount being reduced by one.

updateCoins() Function
-----------------------
Sets coins to 0. Goes thru players hand and adds up coins. The bonus
integer argument is added at the end.
