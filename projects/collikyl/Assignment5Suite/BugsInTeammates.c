Bugs found in Shaine Afzal

Bug #1
Card: Adventurer 
Description: Adventurer does not correctly move itself to the played pile. This error occurs constantly.
Reproduction: Initialize a random gameState. Play  the adventurer card. Immediately after playing the adventurer card examine the cards in the playedPile at position playedCount-1. The adventurer card should be there but it's not. 
Reasoning: The adventurer card is never appropriately removed from the player's hand. As a result both handCount and playedCount are off. 
Recommended Fix: It seems that discardCard is never called for the adventurer card. It could be fixed by calling discardCard at the appropriate handPos of the adventurer card being played, however this may introduce new bugs.
Difficulty to Fix: Low



Bug #2
Function: endTurn()
Description: End turn does not appropriately move played cards into discard pile.
Reproduction: Initialize a gameState with any seed. Insert cards into the played pile for the player whose turn it is. Call endTurn. DiscardCount should = preDiscardCount + handCount + playedCount but it's only the summation of preDiscardCount + handCount. 
Reasoning: Played pile is never iterated through and inserted into discard pile.
Recommended Fix: Follow same procedure as for handPile with playedPile.
Difficulty to Fix: Low
Sample Output: Note - Should include smithy in discard but doesn't. 

Beginning Test for smithy...

Player 0's deck:
#  Card
0  Estate
1  Estate
2  Copper
3  Copper
4  Copper

Player 0's hand:
#  Card
0  Copper
1  Copper
2  Estate
3  Copper
4  Copper
5  Smithy

Player 0's deck:
#  Card
0  Estate
1  Estate

Player 0's hand:
#  Card
0  Copper
1  Copper
2  Estate
3  Copper
4  Copper
5  Copper
6  Copper
7  Copper

Player 0's discard:
#  Card
0  Copper
1  Copper
2  Estate
3  Copper
4  Copper
5  Copper
6  Copper
7  Copper


        Testing finished
		
Bug Report for Teammate 1 Jack Holkeboer

Bug #1
Card: Adventurer 
Description: Adventurer does not correctly move itself to the played pile. This error occurs constantly.
Reproduction: Initialize a random gameState. Play  the adventurer card. Immediately after playing the adventurer card examine the cards in the playedPile at position playedCount-1. The adventurer card should be there but it's not. 
Reasoning: The adventurer card is never appropriately removed from the player's hand. As a result both handCount and playedCount are off. 
Recommended Fix: It seems that discardCard is never called for the adventurer card. It could be fixed by calling discardCard at the appropriate handPos of the adventurer card being played, however this may introduce new bugs.

Bug #2 
Card: Adventurer
Description: This seems to be a significant error as in some cases there is only one card being drawn and added to the player's hand while in other cases no cards are drawn at all despite treasure being in the fullDeck (both deck pile and discard). Additionally, the discardCount/deckCount is bugged as well. The adventurer card is also skipping some treasures in the deck despite having a treasureCount < 2. I've attached some sample outputs to help illustrate these errors. 
Reasoning: I'm unsure as to what the problem is. Both my randomTest and my static test result in drawing one card. Looking at your code, this should not be the case.


