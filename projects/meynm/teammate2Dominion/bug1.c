/* 
Nelson Samayoa
CS 362
Documentation of bugs found
Onid: samayoan

Bug 1: 
	The players score is not always correctly calculated.

The failure: 
	The scoreFor() method sometimes does not calculate the player's score when
	there are point cards (estates, gardens, great_hall) in the deck. If the point
	cards are only in the hand and discard piles, the score will be calculated correctly.
	The conditions required for the bug to show are as follows:
		1. The total number of discard cards (discardCount) is greater than
			the total number of cards in the deck pile (deckCount) OR  
		2. The total number of discard cards (discardCount) is less than
			the total number of cards in the deck pile (deckCount) and the deck has point
			cards at the higher indexes. 
		3. The deck pile contains at least one card that would contribute to their final score.
 
How I found it:
	In my test code I have two test cases that catch this bug. One test cases test the scenario where
	the amount of cards in the deck pile is less that the amount in the discard pile. The other test
	case tests the scenario where the deck pile has more than the discard pile. Upon running both
	portions of test code, the calculated scores came back different from what I calculated manually.
	
Part of code or usage case that causes the bug:
	In the scoreFor() method in dominion.c there are 3 for loops. The last for loop uses the wrong
	max value (it should use state->deckCount but instead uses state->discardCount).
	
	//score from deck
  	for (i = 0; i < state->discardCount[player]; i++)
    {
      if (state->deck[player][i] == curse) { score = score - 1; };
      if (state->deck[player][i] == estate) { score = score + 1; };
	...........

	This means that if the discardCount is less or greater than the deckCount, only some cards from the 	deck pile will be counted or some -1 values will be counted in the final score, resulting in an
	incorrect score for that player.



Bug 2:
	The players score is not always correctly calculated when Garden cards are present.
	The effect of the Garden card is not applied.

The failure: 
	The scoreFor() method does not count all cards when applying the Garden card's effect. The
	Garden card is supposed to give the player 1 point for every 10 cards he or she has (regardless of
	type). However, scoreFor() does not apply the effect at all.

How I found it:
	I have a test case that uses two Garden cards, and 28 Province cards. The expected score then is
	170 because 168 come from the Province cards, then 2 from the Garden cards because the deck has two
	sets of 10 cards. The actual score return is 168.

Part of code or usage case that causes the bug:
	The code at fault is a combination of how scoreFor() calls fullDeckCount() and also the fact that 
	fullDeckCount() does not have a way to count all cards regardless of type. Firstly, scoreFor() calls
	fullDeckCount() passing 0 for the card type, meaning that the number returned is the total count of 
	curse cards, not all cards. Secondly, the fallDeckCount() method doesn't have a way to count all 
	cards, so there is no "quick fix" that can be made to scoreFor(). The fix would be a medium sized
	refactoring of the fullDeckCount() method.



Bug 3:
	The smithy effect is not correctly applied (3 cards are not added to the hand.

The failure: 
	When a player uses the smithy action card, 3 cards should be added to the hand and the
	handcount should be incremented by 3. The dominion code does not currently do that.	

How I found it:
	In cardtest1.c I have tests that check if the smithy effect is correctly applied. I noticed
	that when I ran the tests, the results were never as expected. I stepped through the code
	using the debugger in the Code::Blocks IDE to find the trouble spots.

Part of code or usage case that causes the bug:
	This bug is actually caused by two lines of code. The first spot is in the cardEffect method 
	on the 5th line of the method:
		
		int currentPlayer = whoseTurn(state);

	The problem is incorrect pointer usage. This line is should read like this with the address passed:

		int currentPlayer = whoseTurn(&state);

	The second bit of code that contributed to the issue is actually a bug that I purposely introduced
	earlier in the term. I actually had forgotten I introduced it and had to use the Code::Blocks
	debugger to discover it. The problem is another misuse of pointers in the smithyEffect method 
	that I created:

		drawCard(currentPlayer, &state);

	Should be:
		
		drawCard(currentPlayer, state);
	

Bug 4:
	The Adventurer card's effect isn't properly applied: Hand and discard counts are incorrect.

The failure: 
	When a player plays the Adventurer card, the hand and discard counts are incorrect because
	the adventurer card itself is not removed from the hand.

How I found it:
	In my cardtest2.c code I capture and print the hand count after the adventurer card's 
	effect is applied. It was consistenty returning a hand count that was 1 more than expected,
	and an unchanged discard count.
	I expect the effect to add two treasure cards and then discard the played adventurer card,
	resulting in a net gain of 1 card. The actual result was a net gain of 2 cards. Upon inspection
	I realized that the method responsible for the adventurer effect was not discarding the
	played adventurer card, thus not removing it from the hand and not increasing the discard count.

Part of code or usage case that causes the bug:
	In dominion.c, the bottom of the adventurerEffect method should have a call to discardCard(),
	as all other card effect methods have. adventurerEffect does not have this call, resulting in
	incorrect hand and discard counts.


Bug 5: 
	The Adventurer card's effect always adds only 2 coins, even if silver and gold treasures 
	cards are present.

The failure: 
	When a player plays the Adventurer card, they have to continue drawing cards until two treasure
	cards have been drawn. This bug makes it so that they will always draw two coppers, gaining just
	two coins.
	
How I found it:
	I actually added this bug myself earlier this term. I remembered the spot I changed so 
	already expected it. I also saw the results of the bug in my tests because the coins always
	increased by just two.	

Part of code or usage case that causes the bug:
		In the adventurerEffect method, I added "=copper" to the end and the result was this:
		cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1]=copper		
		The bug I introduced was in the line that was originally 
		cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1]
		

Bug 6:
	The discard count does not cange.

The failure: 
	When a user discards a card, it would be expceted that the discardCount increase. This does
	not occur currently.
		
How I found it:
	I have a test in cardtest3.c that checks the discardCount. I was seeing that the count was
	consistently unchanged. Upon further investigation I found that the count was not being increased
	when a card was discarded.

Part of code or usage case that causes the bug:
	The problem is in the discardCard method of dominion.c. If you read through it you will see that 
	the discardCount is never increase, thus resulting in incorrect discard counts in the game. 


Bug 7:
	Coins incorrectly added when the salvager card is played.
	
The failure: 
	When a player plays the Salvager card, they are asked to discard one card. In return they
	get the value of the discarded card in coins. So if they discarded a Council Room card, they 
	would get 5 coins in return. The bug is causing an incorrect number of coins to be added. So	
	currently if a player discards a Council Room card, they may get more or less than 5 coins.
	
How I found it:
	In my cardtest3 testing I noticed that I could never get the coin number to be what I expected.
	Upon further investigation I saw that it was caused by a mistake in the code.	

Part of code or usage case that causes the bug:
	In the salvagerEffect method, there is a call to handCard().

		state->coins = state->coins + getCost( handCard(choice1, state) );
	
	The handCard method expects the handPos as it's first parameter. Notice that in this case the
	parameter being passed is the choice1 parameter, which is the card as defnied in the CARD enum.
	This means that if the player discards a Province card from the 1st hand position, the coin 
	count that will actually get calculated will be from the card in the 4th position, because 
	Province is the 4th element in the CARD enum. The correct line would look like this:

		state->coins = state->coins + getCost( handCard(handPos, state) );

	When I change that code I do get correct coin counts.	


Bug 8:
	The discard count never changes after discarding a card.	

The failure: 
	After a player discards a card, you would expect their discardCount to increase. The current 
	dominion implementation does not do that correctly.
		
How I found it:
	In cardtest4.c I check the values of discardCount and notice they never changed, even after 
	a player discarded a card. Upong further inspection I saw that the discardCard method was at fault.
		
Part of code or usage case that causes the bug:
	In dominion.c the discardCard() method never increments the discardCount value. To remedy this, 
	the method should have the following line of code:
	
		state->discardCount[currentPlayer]++;


Bug 9:
	When one player plays the Cutpurse card, the other players lose more coins than the value of 
	the copper card (they lose the value of a Gold card).
	
The failure: 
	When one player plays the Cutpurse card, the other players are suppose to forfeit one copper 
	card if they have one. The bug makes the other players lose a GOLD card, which is a lot more
	valuable.	
		
How I found it:
	I introduced this bug for assignment 2 so I already expected it. It did also add a check for it
	in cardtest4.c, so you can visually see the effects.

Part of code or usage case that causes the bug:
	In dominion.c, the cutPurseEffect() method has this buggy line:
		
		if (state->hand[i][j] == gold)
	
	That line should read:	

		if (state->hand[i][j] == copper)

	The result of the bad line is that the other players lose the value of a Gold card rather than
	a copper.
*/
