---------------------------------------------
Teammate Identified Bugs
---------------------------------------------
scoreFor()
* The scoreFor function has a bug which miscounts victory points in the player's deck.
To fix this bug I changed the loop that totals victory points from the deck to loop over the total deck
In 'scoreFor()' I changed line 434
from:
  for (i = 0; i < state->discardCount[player]; i++)

to:
  for (i = 0; i < state->deckCount[player]; i++)


playSmithy()
* The smithy has a bug which causes one too many cards to be drawn.
Smithy was looping to many times causing one additional card to be drawn.
The error was an in the comparison of the for. Instead of '<=' it needed to be '<'.
In 'playSmithy()' I changed line 1270
from:
  for (i = 0; i <= 3; i++)
state->numActions = state->numActions + 2;
to:
  for (i = 0; i < 3; i++)


playVillage()
* The village has a bug which gives too many actions.
To fix this bug I reduced the total amount of actions that 'playVillage'
adds to the players action.
In 'playVillage()' I changed line 1344
from:
  state->numActions = state->numActions + 4;

to:
  state->numActions = state->numActions + 2;



---------------------------------------------
My Introduced Bugs
---------------------------------------------

playRemodel()
* Incorrectly trashing cards. Change line 1324 in 'playRemodel()', the discard statement was incorrectly
trashing the remodel card instead of discarding it.
from:
  discardCard(handPos, currentPlayer, state, 1)

to:
  discardCard(handPos, currentPlayer, state, 0)


* Incorrectly trashing cards. Changed line 1313 in 'playRemodel()' to use 'choice1' instead of 'choice2'.
from:
  int j = state->hand[currentPlayer][choice2];  //store card we will trash

to:
  int j = state->hand[currentPlayer][choice1];  //store card we will trash


playGreatHall()
* Causing player to draw and additional card.
Removed additional 'drawCard()' statement causing player to draw to many.

deleted: this statement followed discardCard() statement. Now only one drawCard call.
  //+1 Card
  drawCard(currentPlayer, state);

* Call to playGreatHall() was never returning a successful value.
Changed return statement to return 0 instead of -1 when the function successfully executes.

from:
  return -1;

to:
  return 0;


---------------------------------------------
Additional Discovered Bugs
---------------------------------------------
playSmithy()
* Incorrectly subtracting the player's actions after playing smithy.
Added statment to decrement the player's actions so player has one less
action after playing smithy.

Added:
  state->numActions = state->numActions-1;             // Decrement actions.


* Incorrectly placing cards in discard pile.
I didn't need to fix any code for this bug. It turned out my tests were incorrect.
I changed my cardtest1 algorithm that was looking though the playedCard pile. It was
incrementing the counter for the number of cards in discard when it found a card in the
played pile, making the test which checked the discard pile fail.

from:
  // Make sure player has 1 smithy card in played card pile.
  for(i = 0; i < testGame->playedCardCount; i++) {
    if(testGame->playedCards[i] == smithy) {        // There is a smithy in played cards.
      smithyDiscardCount++;		// INCORRECTLY INCREMENTING DISCARD COUNT
    }
  }

to:
  // Make sure player has 1 smithy card in played card pile.
  for(i = 0; i < testGame->playedCardCount; i++) {
    if(testGame->playedCards[i] == smithy) {        // There is a smithy in played cards.
      smithyPlayedCount++;		// CORRECTLY INCREMENT PLAYED CARD COUNT.
    }
  }


playAdventurer()
* Handsize incorrectly increasing by 2 instead of 1.
Added code to make sure the adventurer card that was played was discarded from the players hand.

Added:
  // Find hand position of adventurer
  for(i = 0; i < state->handCount; i++) {
    if (state->hand[currentPlayer][i] == adventurer) {
      advenPos = i;       // Get adventurer position.
      break;
    }
    return -1;            // No adventurer in hand so don't let them play one!
  }

  discardCard(advenPos, currentPlayer, state, 0);      // Discard played adventurer card.


* Players action total not decreasing.
Added code to decrement the players action total. Statement was added at the end
of the playAdventurer method.

Added:
  state->numActions = state->numActions-1;


* Player not adding adventurer card to 'played' pile after playing it
This turned out to be an bug in my test suite, not implementation.
I changed my code that totals the number of cards the player had in their
played card pile

From:
  // Make sure player has 1 adventurer card in played card pile.
  for(i = 0; i < testGame->playedCardCount; i++) {
    if(testGame->playedCards[i] == adventurer) {        // There is a adventurer in played cards.
      adventurerDiscardCount++;
    }
  }

to:
  // Make sure player has 1 adventurer card in played card pile.
  for(i = 0; i < testGame->playedCardCount; i++) {
    if(testGame->playedCards[i] == adventurer) {        // There is a adventurer in played cards.
      adventurerPlayedCount++;
    }
  }


* Incorrectly adding the total amount of treasures to players hand
This turned out to be another error in my test method. Resulting from me incorrectly counting
the number of treasures the player has to start with. I was replacing the first treasure in the players
hand later on in my code with a adventurer card, in my fixed code I only count every card except
for the first.

From:
  // Figure out how many treasure in player's hand before playing adventurer.
  for(i = 0; i < testGame->handCount[testGame->whoseTurn]; i++) {
    if(testGame->hand[testGame->whoseTurn][i] == copper || testGame->hand[testGame->whoseTurn][i] == silver || testGame->hand[testGame->whoseTurn][i] == gold ) {
      treasureCount++;
    }
  }

to:
  // Figure out how many treasure in player's hand before playing adventurer.
  for(i = 1; i < testGame->handCount[testGame->whoseTurn]; i++) {
    if(testGame->hand[testGame->whoseTurn][i] == copper || testGame->hand[testGame->whoseTurn][i] == silver || testGame->hand[testGame->whoseTurn][i] == gold ) {
      treasureCount++;
    }
  }

* Incorrectly re-shuffling cards back into deck
* Incorrectly adding the total amount of treasures to players hand
This turned out to be another error in my test method. Resulting from me incorrectly counting
the number of treasures the player has to start with.

From:
  // Figure out how many treasure in player's hand before playing adventurer.
  for(i = 0; i < testGame->handCount[testGame->whoseTurn]; i++) {
    if(testGame->hand[testGame->whoseTurn][i] == copper || testGame->hand[testGame->whoseTurn][i] == silver || testGame->hand[testGame->whoseTurn][i] == gold ) {
      treasureCount++;
    }
  }

to:
  // Figure out how many treasure in player's hand before playing adventurer.
  for(i = 1; i < testGame->handCount[testGame->whoseTurn]; i++) {
    if(testGame->hand[testGame->whoseTurn][i] == copper || testGame->hand[testGame->whoseTurn][i] == silver || testGame->hand[testGame->whoseTurn][i] == gold ) {
      treasureCount++;
    }
  }



playRemodel()
* Trashing an adventurer card doesn't allow user to purchase a garden.
from:
  if ( (getCost(state->hand[currentPlayer][choice1]) + 2) > getCost(choice2) )

to:
  if ( (getCost(state->hand[currentPlayer][choice1]) + 2) < getCost(choice2) )


playVillage()
* Players actions increase when the card the player attempts to play isn't
a village. Action totals were still increasing.
Added check to make sure the card the player is trying to play is actually
a village.

from:
  int playVillage(struct gameState *state, int currentPlayer, int handPos) {
    // Make sure card is village.
    if(state->hand[currentPlayer][handPos] != village) {
      return -1;
    }

to:
  int playVillage(struct gameState *state, int currentPlayer, int handPos) {
    // Make sure card is village.
    if(state->hand[currentPlayer][handPos] != village) {
      return -1;
    }
