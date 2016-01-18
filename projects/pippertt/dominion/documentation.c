/* THIS IS NOT A C FILE!
 *
 *
 *

Documentation for Dominion 
v1.0
By: Thomas "Adam" Pippert


Cards
+++++

Cards are initialized as a variable of enum type CARD (defined in dominion.h), and this variable utilized
in differing ways, dependent on the effect of the card.

Smithy:
The CARD enum is used as the first argument in the function 'cardeffect' to enable 
smithy effects in-game. This triggers a switch statement (case:smithy) to call the function 
drawcard() 3 times (with currentPlay + state as arguments)
inside of a loop, in order to add three cards to the player's hand. After this, the
discard function is called, and the smithy's effects end.

Adventurer:
The CARD enum is used as the first argument in the function 'cardeffect' to enable adventurer 
effects in-game. This triggers a switch statement (case:adventurer)that starts a while loop, 
which ends when the int 'drawntreasure' (having started at 0) is equal to two. This loop first 
checks the 'state' struct data on the size of the current player's deck to check if it is empty. 
Should it be empty, the shuffle function is called for the current player.

Once the deck size is confirmed to be greater than 0, the drawcard function is called with
the int 'cardDrawn' set to the result (result being the top card of the player hand). If
cardDrawn is equal to a treasure type, the int 'drawntreasure' is incremented . If it is not,
the player's handCount is decremented, which effectively removes the card from the hand.

Once the loop has ended with two treasure cards drawn, the counter for the player's temporary hand
'z' is decremented in a while loop until it reaches 0. During that loop, all cards in play
that have been drawn are discarded by changing the state struct's discard count for the current
player.


Methods
+++++++

discardCard():
Arguments: (int handPos, int currentPlayer, struct gameState *state, int trashFlag)

discardCard reduces the number of cards in the player's hand, and adds the selected card to the played
pile. Arguments include the position of the card in the player's hand, the current player ID,
the state struct, and a flag for marking a card is to be trashed.

If the trash flag is set to 0, then the top of the played pile
(contained in the variable playedcardCount) is set to be the card identified by handPos.
Then, the hand position for the played card is set to -1. Another 'if' statement is called
to see if the last card in the the user hand is played, or if there is only one card left in the
user hand. Regardless of which case is true, the total number of cards in the current player's hand
is decremented.

If, however, neither of the prior two conditions (last card in hand / only card) are true,
the last card in the player's hand replaces the discarded card in the state strcut
for the current player.  In this case, the (new) last card is set to -1, then the hand count for the 
current player is decremented.

updatecoins():
Arguments: (int player, struct gameState *state, int bonus)

updatecoins() increases the number of coins for a player. Arguments include the player ID,
the ste struct with the game/player information, and the bonus to add to the player's
coin count.

When the function starts, the coin count is initially reset to 0 in the state struct.
Once this is reset, a 'for' loop cycles through a player's hand array. At each index,
if the card is either a copper, silver, or gold, the equivlent value of that metal
is added to the coin count of the state struct. Once the loop is finished, any bonus
is added, and the function finishes.
*/
