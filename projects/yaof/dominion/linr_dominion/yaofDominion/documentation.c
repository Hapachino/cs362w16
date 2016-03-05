/*
smithy card
------------
In the game, the smithy card gives +3 cards in the hand of the player who used it.
The code implements this by calling the drawCard function three times in a loop and
updating the game state.

adventurer card
------------
In the game, the adventurer card will keep drawing cards until you have two treasure
cards in your hand. The code implements this by using a variable called 'drawntreasure'
which is initialized at 0 in the cardEffect function. The while loop will not terminate
until drawntreasure is equal to 2 or greater. Each card we draw is checked if it's a treasure or not.
If it isn't, we don't add it to our hand. This updates the game state struct in order
to keep track of player hands.

discardCard()
------------
discardCard works by setting the index of the card we are discarding to -1 in the
current player's hand. If the current discarded card is the last card in the hand
array or the only card in hand, we simply subtract the hand count for the current 
player by 1. Otherwise, we replace the discarded hard with the last card we had
in the hand, and then subtract the hand count for the current player by 1. This
is implemented in the game state struct, where all pertinent variables are stored
(hand count and current cards on hand for each player).

updateCoins()
------------
updateCoins works by iterating through every single card in the current player's
hands. If the card is a copper, add 1 to the game state struct variable 'coins'. 
If silver, add 2. If gold, add 3.
*/