***********************************
Teammate identified bug- endTurn()*
***********************************
One of the bugs suggested by teammate Kyle was that endTurn is not discarding the playedCards pile as it should.
I corrected this by looping through the playedCards pile and adding them to the discard pile, setting the value for
that array location to -1, then setting playedCardCount to 0.

******************************************
Teammate identified bugs- adventurerCard()*
******************************************
Kyle also identified that the adventurer card does not get added to the played card pile. I added an if statement
that determines if the card in currentPlayer's hand at handPos is the adventurer card, and if it is it adds it 
to the played card pile. The reason I did it this way is to account for instances where discarding the card might be 
handled by the function that calls adventurerCard(), or when the card is not actually in the players hand such as
being called by the programs I used for testing, the function was called without adventurer actually being the current card.
After doing this 

*****************************************
Teammate identified bug- greatHallCard()*
*****************************************
Jack said that when the Great Hall card was played it was not gaining the player an action. When I fixed the bug I implemented
with the incorrect trash flag being passed to discardCard(), and then ran my test on this card, it was gaining an action as
it was supposed to.

*****************************
Bugs that I added to my code*
*****************************
I changed the trash flag that is passed to the discardCard function for the Great Hall card originally, so I changed it back.
I made the for loop for the Smithy card (i=0; i<=3; i++) however it should have just said i<3, so I changed that back. For the
Village card I changed it from saying state->numActions + 2 to saying state->numActions = state->numActions + 2.

*****************************
Additional bugs that I found*
*****************************
In the initialize game function it did not draw 5 cards into the players hand like it was supposed to, so I fixed that part. In
the fullDeckCount function it was not counting the full deck, it was only counted if there was a certain card in the deck, so I fixed
that by just having a count variable and adding deckCount, discardCount, and handCount. 
