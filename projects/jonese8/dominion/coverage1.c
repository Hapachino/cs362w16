CS362 - Assignment 3 - Emmalee Jones
02/02/2016

File 'dominion.c'
Lines executed:39.97% of 578
Branches executed:48.68% of 417
Taken at least once:39.81% of 417
Calls executed:26.80% of 97
dominion.c:creating 'dominion.c.gcov'

After executing all 4 unit tests and 4 card tests only 39.97% of the 578 lines 
of statements in dominion.c were executed.  Only 48.68% of 417 branches were
executed.  This does not seem unreasonable since I was only testing a few 
specific functions and related functions that were called by those functions.
The more important aspect was how many lines of code were actually used 
within in the functions I called for testing listed in dominion.c.gcov.

Boundary Testing:

1. unittest1.c - updateCoins
A.	Current player recount coin total for each treasure card in hand:
	a.	1 point for each copper card
	b.	2 points for each silver card
	c.	3 points for each gold card
B.	Numbers of points for bonus is added on top of the treasure card points.
C.	No state change should occur for other players.
D.	No state change should occur to the victory card piles and kingdom card piles.
E.	The function should return 0 when completed.

2. unittest2.c - scoreFor
A.	Total Score for  handCount  for each player  
	a.	-1 VP for each curse card
	b.	1 VP point for estate card
	c.	3 VP points for each duchy card
	d.	6 VP points for each province
	e.	1 VP point for great hall card
	f.	1 VP point for every 10 cards in deck rounded for garden card 
B.	2. No state change should occur for other players.
C.	3. No state change should occur to the victory card piles and kingdom card piles.


3. unittest3.c - getWinner
A.	Calculate score for each player, set unused players to score -9999.
B.	Find highest score for players.
C.	Add 1 to players who have less turns.
D.	Find new highest score for players.
E.	Set winners in array.
F.	The function should return 0 when completed.
G.	No state should change for any player. 


4. unittest4.c - isGameOver
A.	Game over if:
B.	Province Cards Stack == 0, return 1
C.	or 3 supply piles are at 0
D.	No state change should occur for other players.
E.	No state change should occur to the victory card piles and kingdom card piles. 
F.	The function should return 0 if game not over.


5. cardtest1.c - smithy
A.	 Current player should receive exactly 3 cards.
B.	 3 cards should come from his own deck.
C.	 No state change should occur for other players.
D.	 No state change should occur to the victory card piles and kingdom card piles.

6. cardtest2.c - adventurer
A.	Reveal cards from your deck until you reveal 2 Treasure cards.
B.	Shuffle if not enough treasure cards, do not shuffle in revealed cards, only shuffle once.
C.	Put those treasure cards in your hand and discard the other revealed cards.
D.	No state change should occur for other players
E.	No state change should occur to the victory card piles and kingdom card piles.


7. cardtest3.c - council_room 
A.	Draws 4 cards from deck to hand of player.
B.	4 cards should come from his own deck.
C.	Adds 1 buy from store to player.
D.	Draws one card for other player to hand.
E.	No state change should occur to the victory card piles and kingdom card piles.


8. cardtest4.c - great_hall
A.	Draw one card from deck to hand of player.
B.	1 card should come from his own deck.
C.	Adds action to players action count.
D.	Add one point to final score, do not test as part of card.
E.	No state change should occur for other players
F.	No state change should occur to the victory card piles and kingdom card piles.
