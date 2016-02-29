business rules

unittest1.c for getCost()
	1. get the cost to buy/gain a card, return integer of cost like 2,3,4,etc.
	2. for cards in dominion system not in the simulation set, return -1 

unittest2.c for updateCoins()
	1. add coin value of all treasure cards and bonus.
	2. add 1 for copper treasure cards.
	3. add 2 for silver treasure cards.
	4. add 3 for gold treasure cards.
	5. add bonus (passed in as parameter).

unittest3.c for isGameOver() - no bugs found.
	1. game is over if supply of province cards is 0
	2. game is over if three supply piles are 0

unittest4.c for fullDeckCount() - no bugs found.
	1. count all cards in deck for a player
	2. count all cards in hand for a player
	3. count all cards in discard for a player
	4. return total count

cardtest1.c for smithy
	1. draw/add 3 cards to player hand
	2. discard from hand

cardtest2.c for adventurer
	1. draw a card from player deck until two treasure cards are drawn
	2. add treasure cards to hand
	3. discard all cards that were drawn

cardtest3.c for council room
	1. draw/add 4 cards to player hand
	2. all other players draw 1 card into their hands
	3. discard from hand 

cardtest4.c for mine
	1. choose a copper or silver treasure card to trash
	2. choose a treasure card one higher from supply to put into hand replacing choice1.
	3. discard from hand
