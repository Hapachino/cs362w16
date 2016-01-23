#include <stdio.h>
#include <stdlib.h>

#include "dominion.h"

#define INITGAME_PASS "initializeGame() PASS: "
#define INITGAME_FAIL "initializeGame() FAIL: "

// int initializeGame(int numPlayers, int kingdomCards[10], int randomSeed, struct gameState *state) {

void testInitializeGame() {
  int i = 0;
  int j = 0;


  int numPlayers = 2;
  int kingdomCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
	       sea_hag, tribute, smithy};
  int randomSeed = 0;

  struct gameState *state = newGame();          // Initialize game state.

  printf("%s", "Hello");
  printf("%d", numPlayers);

  initializeGame(numPlayers, kingdomCards, randomSeed, state);

  // Check number of players.
  if (numPlayers == 2) {
    printf(INITGAME_PASS);
  } else {
    printf(INITGAME_FAIL);
  }
  printf("expects a game with 2 'players', got: ");
  printf("%d", numPlayers);
  printf("\n");

  // Check number of curse cards for 2 players.
  if (numPlayers == 2) {
    if (state->supplyCount[curse] == 10) {
      printf(INITGAME_PASS);
    } else {
      printf(INITGAME_FAIL);
    }
    printf("expects a 2 player game, to contain 10 'curse' cards, got: ");
    printf("%d", state->supplyCount[curse]);
    printf("\n");
  }

  // Check number of victory cards for 2 players.
  if (numPlayers == 2) {
    // Check number of estate cards.
    if (state->supplyCount[estate] == 8) {
      printf(INITGAME_PASS);
    } else {
      printf(INITGAME_FAIL);
    }
    printf("expects a 2 player game, to contain 8 'estate' cards, got: ");
    printf("%d", state->supplyCount[estate]);
    printf("\n");

    // Check number of duchy cards.
    if (state->supplyCount[duchy] == 8) {
      printf(INITGAME_PASS);
    } else {
      printf(INITGAME_FAIL);
    }
    printf("expects a 2 player game, to contain 8 'duchy' cards, got: ");
    printf("%d", state->supplyCount[duchy]);
    printf("\n");

    // Check number of province cards.
    if (state->supplyCount[province] == 8) {
      printf(INITGAME_PASS);
    } else {
      printf(INITGAME_FAIL);
    }
    printf("expects a 2 player game, to contain 8 'province' cards, got: ");
    printf("%d", state->supplyCount[province]);
    printf("\n");

  }

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
      printf("%d", i);
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
      printf("%d", i);
      printf("' to start 5 cards in 'hand', got: ");
      printf("%d", state->handCount[i]);
      printf("\n");

    } else {  // All other players always start the game with 10 cards in their deck.
      // Deck count.
      if (state->deckCount[i] == 10) {
        printf(INITGAME_PASS);
      } else {
        printf(INITGAME_FAIL);
      }
      printf("expects 'Player ");
      printf("%d", i);
      printf("' to start with 10 cards in 'deck', got: ");
      printf("%d", state->deckCount[i]);
      printf("\n");

      // Hand count.
      if (state->handCount[i] == 0) {
        printf(INITGAME_PASS);
      } else {
        printf(INITGAME_FAIL);
      }
      printf("expects 'Player ");
      printf("%d", i);
      printf("' to start with a 0 cards in 'hand', got: ");
      printf("%d", state->handCount[i]);
      printf("\n");
    }
  }


  // Check make up of hands and decks.
  // Check total number of estate and copper cards for each player.
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
    printf("%d", i);
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
    printf("%d", i);
    printf("' deck to start with 7 'copper' cards, got: ");
    printf("%d", numCopper);
    printf("\n");
  }

  // Check embargo tokens were set to 0 for all supplies.
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


  // state->phase = 0;
  // Check state phase is initialized to 0.
  if(state->phase == 0) {
    printf(INITGAME_PASS);
  } else {
    printf(INITGAME_FAIL);
  }
  printf("expects game to start with 0 'phase', got: ");
  printf("%d", state->phase);
  printf("\n");

  // state->numActions = 1;
  // Check state action initialization to 0.
  if(state->numActions == 1) {
    printf(INITGAME_PASS);
  } else {
    printf(INITGAME_FAIL);
  }
  printf("expects game to start with 1 'action', got: ");
  printf("%d", state->numActions);
  printf("\n");

  // state->numBuys = 1;
  if(state->numBuys == 1) {
    printf(INITGAME_PASS);
  } else {
    printf(INITGAME_FAIL);
  }
  printf("expects game to start with 1 'buy', got: ");
  printf("%d", state->numBuys);
  printf("\n");

  // state->playedCardCount = 0;
  if(state->playedCardCount == 0) {
    printf(INITGAME_PASS);
  } else {
    printf(INITGAME_FAIL);
  }
  printf("expects game to start with 0 cards 'played', got: ");
  printf("%d", state->playedCardCount);
  printf("\n");

  // state->whoseTurn = 0;
  if(state->whoseTurn == 0) {
    printf(INITGAME_PASS);
  } else {
    printf(INITGAME_FAIL);
  }
  printf("expects game to start with 'Player 0' starting player, got Player: ");
  printf("%d", state->whoseTurn);
  printf("\n");

  // state->handCount[state->whoseTurn] = 0;
  if(state->handCount[state->whoseTurn] == 5) {
    printf(INITGAME_PASS);
  } else {
    printf(INITGAME_FAIL);
  }
  printf("expects game to start with 5 'cards' in Player 0's hand, got: ");
  printf("%d", state->handCount[state->whoseTurn]);
  printf("\n");

}


int main() {
  testInitializeGame();
  return 0;
}
