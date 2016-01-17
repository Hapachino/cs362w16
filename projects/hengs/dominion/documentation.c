Stephen Heng
CS362 Winter 2016
Assignment 2: documentation.c

1. The Smithy card allows the player to add 3 cards from the deck into
the player's hand. It will cost the player 4 coins to obtain the smithy card.
In the playSmithy function, the function runs in a loop in the drawCard function
for 3 times to get 3 cards out of the deck and into the player's hand.
Afterwards, the card is discarded from the hand with the discard function.

2. The Adventurer card allows the player to keep drawing cards until 2 treasure
cards are discovered and added to the hand. Anything that is not a treasure card
is discarded. The cost of the Adventurer card is 6 coins. The function will 
drawCard and count the number of treasure card until it reaches 2 cards. The 
function runs in a loop until 2 treasure cards are reached.

3. The discardCard function takes as parameters hand position(handPos), 
the current player(currentPlayer), the state of the game(state), and the trash 
flag which is an integer. It will first check for the trashflag signal to indicate
if the card is removed from the player's deck. If the flag is not set off,
the card will be added to the playedCards. It will check if the card was played
or it will be moved to the discard pile. It will then update the hand count
and the number of cards in the hand.

4. The updateCoins function takes as parameters the player, the game state, and the bonus.
It will first reset the coin count and then add up all the treasure cards in the player's
hand and total up the coin count. It has if statements for copper, silver and gold and will
return the total amount of all the treasure cards.
