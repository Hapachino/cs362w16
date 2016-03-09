Jennifer Frase
Cs 362 Assignment 5

Fixed Bugs found through GDB:
1: Charles Hardes found bug for adventurer
2: Yunsik Choi's found bug for smithy
3: unit test found bug for scoreFor()
4: unit test found bug for scoreFor() specifically the gardens score

/**Charles Hardes's Bugs: (sent three but they are really all the same bug)**/
Adventurer:
Charles found that for the adventurer card 4 extra cards were drawn, each
other player recieved an additional card and buy were incremented. This sounded a
lot like the council room card was being played instead of the adventurer card. So
During debugging I set a break point with GDB at playAdventurer to test to see if
I was entering the function. When I did hit the break I knew the card was being called
so I stepped through the function to see why those other things were happening. The
adventurer card worked as needed but when the function returned it did not exit the
switch statement and so entered the code for council room which was right after
adventurer. Going back to the code I noticed that there was no return statement for
the adventurer code in the switch statement. Putting return in front of the 
playAdventurer call fixed the bug:
	return playAdventurer(state, handPos); 						line 673
	
Since I did not intend to introduce this bug, I did go and look at my other switch
statement refactored function calls, and it turned out that I simply forgot to add
return statements to all those calls, so I fixed those while I was at it.

/**Yunsik Choi's Bugs:**/
Adventurer:
Yunsik's adventurer test found that there was a discrepency between the expected and
tested deck and discard numbers. He provided some of his test numbers for the 
deck and discard and when I added them together, then subtracted one from the other
I found that there were the right number of cards overall between the two provided 
sets. So this was not a problem with the number of cards in the hand or missing(trashed)
cards. Once I determined this I went to run his test to debug dominion. However,
the test segfaulted on discardCard at the line:
	state->playedCards[state->playedCardCount] = state->hand[currentPlayer][handPos];
I put a break at this function and went through the variables that are being accessed,
and found that the playedCardCount was 4228837 which is way above the size of the array
(500). I think this is a problem with his test and not my function since it runs fine
in Charles and my tests. As a result I decided to simply comment out the discardCard 
call for the adventurer card. Once I did this the test ran fine. However, I still
could not verify the results that Yunsik got. When I ran his tests the test results
did not say any tests failed. It is possible that he modified his code, which resulted
in the bug, however I cannot verify this.

Smithy:
For Yunsik's smithy test he found that there was a missing card from the currentPlayer's
hand. When I walked through the code in GDB this was because of the call to discard was
called twice in a row, with the second call being:
    discardCard(handPos-1, currentPlayer, state, 0);			line 1286
This line tries to discard the card before the smithy as well.
By getting rid of this line the bug was fixed.

/**My Bugs:**/
I did not have any tests for the other cards where I introduced bugs, so I simply
went in and changed the lines that I had previously modified. 

Remodel:
The line in the function playRemodel:
    discardCard(handPos, currentPlayer, state, 1);				line 1303
trashes the remodel card instead of adding it to the playedCards array. To fix this
I changed the 1 at the end of the discard call to 0.

Mine:
For the playMine function the line:
    gainCard(choice2, state, 1, 0);								line 1340
always gives the first player the card instead of the currentPlayer, so the 0 at the
end of the function call was changed to currentPlayer.

/**Unit Test Bugs**/
scoreFor():
When I ran the unit test for scoreFor() it said that the deck scores were 0 when they
should not have been and the discard score were too low as well, though the number
varied in this case. When I used GDB to inspect the code I found that when the deck
count was 0, scoreFor() was still looking at the cards in the current player's deck.
I did this by watching the score value while inside scoreFor(). Once this was seen
I stepped through the code and found that the part that scores for the deck has a
for conditional on the discard count instead of the deck count:
	for (i = 0; i < state->discardCount[player]; i++) 			line 447
This bug results in my test getting erroneous results for the discard count and 0
for the deck count. I fixed the bug by changing discardCount to deckCount.

Once I fixed this bug I did find another bug, which was that gardens would not 
calculate the right score because of an error in the usage of fullDeckCount().
This function returns the number of card in the entire player's possible cards that
match the given card type. Since the scoreFor function only asks for the number of
curse cards the player has and not all the cards, the gardens card doesn't calculate
right. This bug was found after my unit test always returned 0 for the gardens. I then
walked through the code with GDB, watching the score. Since it never changed, I set
a break at fullDeckCount and found that it always returned 0. Once I looked at how
it counted cards I noticed that it would only add to the count if the looked at card
was the right type:
	if (state->hand[player][i] == card) count++; 				line 330
Looking back at the call to fullDeckCount, I noticed it is only called once where
the looked for card is 0(curse):
	fullDeckCount(player, 0, state)								line 432
In order to fix this the call it is easist just to add all the counts for all the
arrays that store cards for the player.
  int cardCount = 0;  											line 421
  
  cardCount = state->handCount[player] + state->discardCount[player] + 
  state->deckCount[player];
While the new variable was not absolutely necessary, all the arrays would make the 
line to calculate the score overly long, so in order to keep readability, I created a 
new variable to take the addition out of calculating the score. This also helps to
reduce repeated code since the same value is used to calculate the scores from the
hand, deck, and discard.

(Please note that after these were fixed I noticed that I was still getting an error.
However, this time all the returned scores were compared against the same number 50,
which should not have happened so I went back to look at my test, and I forgot to
change the comparison score for the gardens on two of my tests. So I fixed that as well.)


