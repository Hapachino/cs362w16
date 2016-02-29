/*
Bugs found by teammates:

note: bugs found by both teammates were condensed down to one

Adventurer bugs :
1. Treats silvers as non - coin cards.

This was a bug I introduced so I knew where it was, however using GDB with a stop when it checks the cards it was seen that with drawing a silver card when checking if it counts as a valid card it was not being counted.  

Code changed from 
	if (cardDrawn == copper || cardDrawn == gold) to
	if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)

2. The adventurer card is not being added to the played card pile(and the playedCardCount variable is not being incremented).

Added a line to discard the card - 

discardCard(handPos, currentPlayer, state, 0);


Mine bugs :
1. Failed to add chosen card to player's hand when it cost less than allowed.

This bug was also the same bug as 2, since it was not accepting valid choices it would not put a valid choice in its hand. See below for fix

2. Incorrectly added the chosen card to player's hand when it cost more than allowed.

Found a bug where the the greater than sign should have been a less that sign changed to code below:

if ( (getCost(state->hand[currentPlayer][choice1]) + 3) < getCost(choice2) )
{
return -1;
}

This make it so if choice1 + 3 is less than choice2 we know its invalid and returns -1

3. Incorrectly allowed a non - coin card to be chosen and added to a player's hand.

When going through the code with debugger, the was a line that incorrectly checking if choice2 was a treasure card, specifically copper through gold. Changed line to

if (choice2 < copper || choice2 > gold) 
{
return -1;
}


this makes it so if choice 2 is not a treasure it returns -1

4. Trashed card is added to the discard pile rather than being removed from game.

When it called discardCard was putting in a 0 for a paramater which sets it to not be trashed, changed 1 so it would trash the card.

discardCard(i, currentPlayer, state, 1);


Remodel bugs :
1. The trashed card is removed from player's hand even when chosen card is too expensive (and, thus, not added to player's hand)

Using GDB found that its removing the trashed card before it checks if price is acceptable, making it so the card is always trashed even if later to be found an invalid choice. Moved line below the check to see if choices are valid.

2. Trashed card is added to the playedCard pile rather than being removed from game.

When calling discardCard was passing the incorrect parameter as a flag to the function so it was not being discarded. Changed to 
discardCard(i, currentPlayer, state, 1);


Smithy bugs :
1. An incorrect number of cards are added to the player's hand.

For loop to call draw card was running 1 to many times changed i <= 3 to i < 3 so will only call drawcard 3 times.

Village :
1. Actions not set to 2 after card played

This not found to be a bug, it supposed to add 2 actions not set the player to 2 remaining actions.

Council Room :
1. Not rewarding 1 buy to player

When running GDB found there was never a call to increase the players buy count, added line in

state->numBuys++;

scoreFor Method :
1. Plater 1 and 2 scored inaccurately

Using GDB found that when checking the deck, was using discardCount for number of cards to check rather than deckCount causing inaccurate counting.  In addition the only time the function to count all cards for the players inside this function to help score for gardens, this was incorrectly counting, and only counting the card passed in.  Changed to just be totalCards calculated by adding deckCount, discardCount, and handCount together.


Self Introduced Bugs:

Baron:
1. While loop was not correctly going into based on the wrong boolean check. 

int card_not_discarded = 0;//Flag for discard set!
while (card_not_discarded){
...
}

card_not_discarded incorrectly set to 0 corrected to be:

int card_not_discarded = 1;//Flag for discard set!
while (card_not_discarded){
...
}


Notes:

Refactoring tests to work on teammates code went well for smithy, council_room, and adventurer simply calling their versions of the function and changing around the to match their paramters.  When looking at remodel, because they did not have a seperate function like I had, The code would have be changed to go through the cardeffect function found in dominion.c, which is the normal way cards are called. In retrospect this would have been a better way to call every test, passing in which card I wanted to test, and having that case call thier functions rather than calling the functions individually.  This would create a more coherent test suite, but i would like to test cardEffect  thoroughly before swithcing to this method to make sure bugs are not filtering down into the actual card tests.

*/