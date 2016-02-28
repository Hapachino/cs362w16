Todd Waddell
CS 362 400 W16
Assignment 5

My teammates, Juan Solis and Myles Chatman, reported finding the following bugs in my code:
	1.  Adventurer draws 3 treasure cards instead of two.  dominion.c:1165  fixed
	2.  Smithy card not correctly discarded from hand.  dominion.c:1049 fixed
			This is an error in the discardCard() function.  Discard incorrectly reads trash flag and puts all cards into the 
			played card pile.
	3.  Reported issue with too many cards in hand after playing adventurer.  Report indicated that issue was related to adventurer
			drawing too many cards.  Fixed in item 1, above.
	4.  Juan Solis reported that isGameOver() (dominion.c:390) is not checking the supply piles to sea_hag and treasure_map.  
			I fixed this by setting the supply pile loop from i <= treasure_map. dominion.c:404
	5.  Juan also reported a bug in the discardCard() function (Smithy card is not incrementing the playedCardsCount by 1) wherein the card should be placed in the played card function after play.  And that at the end of turn, the played card function should be shuffled into the deck.  There is an interesting discussion about this on piazza (https://piazza.com/class/iip31fywxe72b0?cid=119) In my interpretation, the fix is to place the cards in the played card file if the trash flag is set and correctly interpreted.  Then code should be added to move the  played card to the discard pile if the trash flag is not thrown.m  dominion.c: 1052 fixed.

My bugs:
	1.  Adventurer: The first bug I introduced was the adventurer draws too much treasure.  Myles and Juan found that one.  Fixed.
	2.  smithyEffect: Bug introduced: changed trash flag to 1.  Fixed.
	3.  feastEffect: Bug introduced: changed update coins to 4.  Fixed.
	4.  cutpurseEffect: Bug introduced: changed coin from copper to gold. Fixed.