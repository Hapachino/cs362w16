#include <stdio.h>
#include <stdlib.h>

#include "dominion.h"

#define INITGAME_PASS "initializeGame() PASS: "
#define INITGAME_FAIL "initializeGame() FAIL: "


void testInitializeGame() {
  int i = 0;
  int j = 0;

  int numPlayers = 0;
  int kingdomCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
	       sea_hag, tribute, smithy};
  int randomSeed = -1;                          // Set randomSeed to less than 0 so it is based off system clock in the initializeGame method.
  int successfulInit = 0;                       // Variable to hold if the game was created successfully or not.

  struct gameState *state = newGame();          // Initialize game state.


  printf("\n***** TESTING INITIALIZE GAME *****\n");
  for(numPlayers = 0; numPlayers < MAX_PLAYERS+2; numPlayers++) {               // Create games with less than, equal to, and more players that supported.

    // Initialize game with valid game values.
    successfulInit = initializeGame(numPlayers, kingdomCards, randomSeed, state);

    // Make sure game successfully starts if at least 2 players are playing and less than or equal to the max number of players.
    if(successfulInit != -1 && (numPlayers > 1 && numPlayers <= MAX_PLAYERS)) {
      printf(INITGAME_PASS);
    } else if (successfulInit == -1 && numPlayers < 2) {            // Prevented game from being created with less than 2 players.
      printf(INITGAME_PASS);
    } else if (successfulInit == -1 && numPlayers > MAX_PLAYERS) {  // Prevented game from being created with more than 4 players.
      printf(INITGAME_PASS);
    } else {                                                        // No expected behavior occured so print fail.
      printf(INITGAME_FAIL);
    }
    printf("expects creation of a game with %d number of players to players to %s\n", numPlayers, successfulInit != -1 ? "SUCCEED" : "FAIL");

    if (successfulInit == -1) {     // Game wasn't successfully created so don't continue testing its other attrs.
      continue;
    }


    // Check number of players.
    if (state->numPlayers == numPlayers) {
      printf(INITGAME_PASS);
    } else {
      printf(INITGAME_FAIL);
    }
    printf("expects a game with %d 'players', got: %d", numPlayers, state->numPlayers);
    printf("\n");


    // Check player 0 is starting the game.
    if(state->whoseTurn == 0) {
      printf(INITGAME_PASS);
    } else {
      printf(INITGAME_FAIL);
    }
    printf("expects game to start with 'Player 1' as indicated by '0', got Player: ");
    printf("%d", state->whoseTurn);
    printf("\n");


    // Check number of curse cards for 2 players.
    int expectedCurses = 0;                                                     // Variable to hold expected curse count.

    if (numPlayers == 2) {
      expectedCurses = 10;

      if (state->supplyCount[curse] == expectedCurses) {
        printf(INITGAME_PASS);
      } else {
        printf(INITGAME_FAIL);
      }

    } else if(numPlayers == 3) {
      expectedCurses = 20;

      if (state->supplyCount[curse] == expectedCurses) {
        printf(INITGAME_PASS);
      } else {
        printf(INITGAME_FAIL);
      }

    } else {
      expectedCurses = 30;
      printf(INITGAME_PASS);

    }
    printf("expects a %d player game, to contain %d 'curse' cards, got: %d\n", numPlayers, expectedCurses, state->supplyCount[curse]);


    // Check number of victory cards for 2 players.
    int expectedSupply = 0;   // Variable to hold expected quantity of each victory card available.

    if (numPlayers == 2) {
      expectedSupply = 8;
    } else {
      expectedSupply = 12;    // Any number of players not equal to 2 will have 12 supply of each victory card.
    }

    // Check number of estate cards.
    if (state->supplyCount[estate] == expectedSupply) {
      printf(INITGAME_PASS);
    } else {
      printf(INITGAME_FAIL);
    }
    printf("expects a %d player game, to contain %d 'estate' cards, got: %d\n", numPlayers, expectedSupply, state->supplyCount[estate]);

    // Check number of duchy cards.
    if (state->supplyCount[duchy] == expectedSupply) {
      printf(INITGAME_PASS);
    } else {
      printf(INITGAME_FAIL);
    }
    printf("expects a %d player game, to contain %d 'duchy' cards, got: %d\n", numPlayers, expectedSupply, state->supplyCount[duchy]);

    // Check number of province cards.
    if (state->supplyCount[province] == expectedSupply) {
      printf(INITGAME_PASS);
    } else {
      printf(INITGAME_FAIL);
    }
    printf("expects a %d player game, to contain %d 'province' cards, got: %d\n", numPlayers, expectedSupply, state->supplyCount[province]);



    // Check starting deck and hands.
    // Check total number of cards for each player.
    for (i = 0; i < numPlayers; i++) {
      // Player 0 only starts with 5 cards in deck because they draw.
      if (i == 0) {
        // Deck count.
        if (state->deckCount[i] == 5) {       // Player 0's deck.
          printf(INITGAME_PASS);
        } else {
          printf(INITGAME_FAIL);
        }
        printf("expects 'Player ");
        printf("%d", i+1);
        printf("' to start with 5 cards in 'deck', got: ");
        printf("%d", state->deckCount[i]);
        printf("\n");

        // Hand count.
        if (state->handCount[i] == 5) {
          printf(INITGAME_PASS);
        } else {
          printf(INITGAME_FAIL);
        }
        printf("expects 'Player ");
        printf("%d", i+1);
        printf("' to start 5 cards in 'hand', got: ");
        printf("%d", state->handCount[i]);
        printf("\n");

      } else {  // All other players always start the game with 10 cards in their deck.
        // Deck count for non-starting players.
        if (state->deckCount[i] == 10) {
          printf(INITGAME_PASS);
        } else {
          printf(INITGAME_FAIL);
        }
        printf("expects 'Player ");
        printf("%d", i+1);
        printf("' to start with 10 cards in 'deck', got: ");
        printf("%d", state->deckCount[i]);
        printf("\n");

        // Hand count for non-starting players.
        if (state->handCount[i] == 0) {
          printf(INITGAME_PASS);
        } else {
          printf(INITGAME_FAIL);
        }
        printf("expects 'Player ");
        printf("%d", i+1);
        printf("' to start with a 0 cards in 'hand', got: ");
        printf("%d", state->handCount[i]);
        printf("\n");
      }
    }


    // Check make up of hands and decks.
    // Check total number of estate and copper cards for each player.
    // Each player should have a total of 7 copper and 3 estate regardless if they started or not.
    for (i = 0; i < numPlayers; i++) {                // Loop through each player.
      int numEstates = 0;
      int numCopper = 0;

      // Loop through each card in player's deck.
      for (j = 0; j < state->deckCount[i]; j++) {
        if (state->deck[i][j] == estate) {
          numEstates++;
        } else if(state->deck[i][j] == copper) {
          numCopper++;
        }
      }

      // Loop through each card in player's hand (doing this because player 0 starts with cards in hand).
      for (j = 0; j < state->handCount[i]; j++) {
        if (state->hand[i][j] == estate) {
          numEstates++;
        } else if(state->hand[i][j] == copper) {
          numCopper++;
        }
      }

      // Check number of estates for each player.
      if (numEstates == 3) {
        printf(INITGAME_PASS);
      } else {
        printf(INITGAME_FAIL);
      }
      printf("expects 'Player ");
      printf("%d", i+1);
      printf("' deck to start with 3 'estate' cards, got: ");
      printf("%d", numEstates);
      printf("\n");

      // Check number of copper for each player.
      if (numCopper == 7) {
        printf(INITGAME_PASS);
      } else {
        printf(INITGAME_FAIL);
      }
      printf("expects 'Player ");
      printf("%d", i+1);
      printf("' deck to start with 7 'copper' cards, got: ");
      printf("%d", numCopper);
      printf("\n");
    }

    //Check embargo tokens were set to 0 for all supplies.
    int numEmbargo = 0;

    for (i = 0; i <= treasure_map; i++) {
      if(state->embargoTokens[i] != 0)
        numEmbargo++;
    }
    if (numEmbargo == 0) {
      printf(INITGAME_PASS);
    } else {
      printf(INITGAME_FAIL);
    }
    printf("expects game to start with 0 'embargo tokens', got: ");
    printf("%d", numEmbargo);
    printf("\n");
    /********* Test end *********/

    // Check Player 0's (first player who starts game) state.
    // state->outpostPlayed = 0;
    // Check number of outposts played.
    if(state->outpostPlayed == 0) {
      printf(INITGAME_PASS);
    } else {
      printf(INITGAME_FAIL);
    }
    printf("expects game to start with 0 'outposts' played, got: ");
    printf("%d", state->outpostPlayed);
    printf("\n");


    // Check phase is initialized to 0 and player 1 is up.
    if(state->whoseTurn == 0 && state->phase == 0) {
      printf(INITGAME_PASS);
    } else {
      printf(INITGAME_FAIL);
    }
    printf("expects 'Player 1' to start with 'phase 0', got: %d \n", state->phase);


    // Check state action initialization to 1 and player 1 is up.
    if(state->whoseTurn == 0 && state->numActions == 1) {
      printf(INITGAME_PASS);
    } else {
      printf(INITGAME_FAIL);
    }
    printf("expects 'Player 1' to start game with 1 'action', got: %d\n", state->numActions);


    // Check state number of buys initialization is set to 1 and player 1 is up.
    if(state->whoseTurn == 0 && state->numBuys == 1) {
      printf(INITGAME_PASS);
    } else {
      printf(INITGAME_FAIL);
    }
    printf("expects 'Player 1' to start game with 1 'buy', got: %d\n", state->numBuys);


    // Check the total number of cards that have been played is set to 0.
    if(state->playedCardCount == 0) {
      printf(INITGAME_PASS);
    } else {
      printf(INITGAME_FAIL);
    }
    printf("expects game to start with 0 cards 'played', got: %d\n", state->playedCardCount);

  } // End player variation loop.

}


int main() {
  testInitializeGame();
  return 0;
}
