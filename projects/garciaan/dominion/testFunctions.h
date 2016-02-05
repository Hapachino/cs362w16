#ifndef _TEST_FUNCTIONS_H
#define _TEST_FUNCTIONS_H


//Used for compare state
enum game_state_vars {
  num_players = 0,
  supply_count,
  embargo_tokens,
  outpost_played,
  outpost_turn,
  whose_turn,
  num_phase,
  num_actions,
  num_coins,
  num_buys,
  player_hand,
  player_hand_count,
  player_deck,
  player_deck_count,
  player_discard,
  player_discard_count,
  played_cards,
  played_card_count,
  other_player,
  last_tester = other_player
};

//Error flag
int ERROR;

//Functions that I have created to help with the test suite

int totalDeckCount(int player, struct gameState *state);
int countTreasures(int player, struct gameState *state); //use updateCoins to play, this just counts coins in hand and returns total
int discardAll(int player, struct gameState *state);
int discardHand(int player, struct gameState *state);
int numDiscards(int player, struct gameState *state);
int checkHand(int orig_hand_count, int offset, int player, struct gameState *state);
int numDeck(int player, struct gameState *state);
int initTestGame(int numPlayers, int kingdomCards[10], int randomSeed, struct gameState *state);
int initTurn(int player, struct gameState *state);
int checkDeck(int player, struct gameState *previousState, struct gameState *state);
void compareStates(struct gameState *state1, struct gameState *state2,int* test, int *results, int verbose);
void createCompareStateArray(int *array, int default_num);
int checkStates(struct gameState *state1, struct gameState *state2, int *excludes, int verbose);
int checkOtherPlayer(struct gameState *state1, struct gameState *state2, int player, int verbose);
void checkError(int pass);
void resetError();
void printResults();
void printDeck(struct gameState *state, int player);
void printHand(struct gameState *state, int player);
void printDiscard(struct gameState *state, int player);
int contains(int* array, int size, int val);
void resetCards(struct gameState *state, int player); 

//signal handlers
void timeout(int signum);
void handle_segfault(int signum);

#endif