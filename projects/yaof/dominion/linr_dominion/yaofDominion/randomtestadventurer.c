/* -----------------------------------------------------------------------
 * Faye Yao
 * CS 362
 * Adventurer Card Unit Test
 * 
 * This is a unit test for the adventurer card in Dominion. We randomize
 * the tests by randomizing the deck state for the player playing
 * the adventurer card. We ensure that there's at least two treasure
 * cards in the deck or discard deck of the player. The player's hand
 * is also randomized.
 *
 * We test for:
 * 1) Does the adventurer keep drawing from the deck until the player
 * that played it has two treasure cards?
 * 2) Does it successfully change the deck/discard state for only the player
 * that played the card?
 * 3) Is the rest of game state intact? No other states should change except
 * the player that played the adventurer.
 * -----------------------------------------------------------------------
 */

#include <math.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <time.h>
#include <stdlib.h>
#include "compareStates.h"

int randomCoin() {
    // generate a random int between 1-100
    int random = rand() % 100 + 1;
    if (random <= 25)
        return copper;
    else if (random <= 50)
        return silver;
    else if (random <= 75)
        return gold;
    else
        return 0;
}

int main() {
    PutSeed(-1);
    int j, p, r, treasures, zero, randomHandCount, randomDeckCount, randomDiscardCount;
    int seed = floor(Random() * 1000);
    int numPlayer = 4; // we can reasonably expect the max players to be 4
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G, copyG;

    srand(time(NULL));

    printf ("TESTING RANDOMIZED playAdventurer:\n");
    printf("---------------------------------\n");
    printf("Test if each player 1 through 4 can play Adventurer correctly.\n");
    for (p = 0; p < numPlayer; p++)
    {
        printf("Testing if Player %i can playAdventurer properly.\n", p + 1);
        printf("---------------------------------\n");
        memset(&G, 23, sizeof(struct gameState));   // clear the game state
        r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
        G.whoseTurn = p;
        memset(G.deck[p], 0, sizeof(int) * MAX_DECK);
        memset(G.discard[p], 0, sizeof(int) * MAX_DECK);
        memset(G.hand[p], 0, sizeof(int) * MAX_HAND);
        // add +2 to deck/discard count so that it is at least 4
        randomDeckCount = rand() % (MAX_DECK + 1 - 2) + 2;
        randomDiscardCount = rand() % (MAX_DECK + 1 - 2) + 2;
        // roll a random hand count somewhere between 2 - (deckCount + discardCount)
        randomHandCount = rand() % ((randomDeckCount + randomDiscardCount) + 1 - 2) + 2;
        G.deckCount[p] = randomDeckCount;
        G.discardCount[p] = randomDiscardCount;
        G.handCount[p] = randomHandCount;
        for (j = 0; j < randomDeckCount; j++)
        {
            int card = rand() % treasure_map;
            if (card == copper || card == silver || card == gold)
                treasures += 1;
            G.deck[p][j] = card;
        }
        for (j = 0; j < randomDiscardCount; j++)
        {
            int card = rand() % treasure_map;
            if (card == copper || card == silver || card == gold)
                treasures += 1;
            G.discard[p][j] = card;
        }
        for (j = 0; j < randomHandCount; j++)
        {
            int card = rand() % treasure_map;
            G.hand[p][j] = card;
        }
        // put some treasures in the deck if it was less than 2 in our randomized 
        // deck
        while (treasures < 2)
        {
            int discardOrDeck = rand() % 1 + 1;
            if (discardOrDeck == 1)
            {
                int pos = rand() % (randomDiscardCount);
                G.discard[p][pos] = randomCoin();
            }
            else
            {
                int pos = rand() % (randomDeckCount);
                G.deck[p][pos] = randomCoin();
            }
            treasures += 1;
        }
        int adventurerPos = rand() % randomHandCount;
        G.hand[p][adventurerPos] = adventurer;
        memcpy(&copyG, &G, sizeof(struct gameState));
        printf("Random set-up finished, playing the Adventurer Card!\n");
        cardEffect(adventurer, 0, 0, 0, &G, adventurerPos, &zero);
        printf("Checking if player drew two cards successfully ...\n");
        if (G.handCount[p] != randomHandCount + 2)
        {
            printf("Player did not draw two cards successfully. Expected handCount: %i, Actual handCount: %i\n", randomHandCount + 2, G.handCount[p]);
        }
        // if the first three cards in their hand are still -1, then they didn't draw a card for
        // one of those slots
        // we check the last two cards to see if it's either the copper or gold that we should've drawn from the
        // deck
        printf("Checking player hand contents to confirm if they're treasures ...\n");
        for (j = randomHandCount; j < randomHandCount + 2; j++)
        {
            if (!(G.hand[p][j] == copper || G.hand[p][j] == silver || G.hand[p][j] == gold))
                printf("Player did not draw a copper, silver or gold card that we put into the deck. Drew a card that wasn't a treasure card at position %i! Card Value: %i\n", j, G.hand[p][j]);
            if (G.hand[p][j] == -1)
            {
                printf("Player did not draw a treasure card successfully in their hand at position %i.\n", j);
            }
        }
        printf("Checking the gameState for all other players to make sure it wasn't modified... \n");
        for (j = 0; j < numPlayer; j++)
        {
            if (j == p)
                continue;
            printf("Testing if Player %i deck values have changed at all ... (they shouldn't)\n", j + 1);
            if (cmpDeckCount(&G, &copyG, j))
                printf("Deck Count has changed between copied and modified game state!\n");
            if (cmpDiscard(&G, &copyG, j))
                printf("Discard deck has changed between copied and modified game state!\n");
            if (cmpDiscardCount(&G, &copyG, j))
                printf("Discard count has been changed between copied and modified game state!\n");
            if (cmpDeck(&G, &copyG, j))
                printf("Deck has changed between copied and modified game state!\n");
        }
        printf("Testing general game state variables if they've been changed ...\n");
        printf("This will test to see if our copied game state before we performed playAdventurer is equal to the modified game state.\n");
        
        if (cmpPlayedCards(&G, &copyG) == 0)
            printf("playedCards hasn't changed between copied and modified game state!\n");
        if (cmpPlayedCardCount(&G, &copyG) == 0)
            printf("playedCardCount hasn't changed between copied and modified game state!\n");
        if (cmpPhase(&G, &copyG))
            printf("phase has changed between copied and modified game state!\n");
        if (cmpWhoseTurn(&G, &copyG))
            printf("WhoseTurn has changed between copied and modified game state!\n");
        if (cmpNumActions(&G, &copyG) == 0)
            printf("numActions hasn't changed between copied and modified game state!\n");
        if (cmpOutpostPlayed(&G, &copyG))
            printf("OutpostPlayed has changed between copied and modified game state!\n");
        if (cmpNumPlayers(&G, &copyG))
            printf("NumPlayers has changed between copied and modified game state!\n");
        if (cmpNumBuys(&G, &copyG))
            printf("NumBuys has changed between copied and modified game state!\n");
        if (cmpOutpostTurn(&G, &copyG))
            printf("OutpostTurn has changed between copied and modified game state!\n");
        if (cmpSupplyCount(&G, &copyG))
            printf("SupplyCount has changed between copied and modified game state!\n");
        printf("Done checking game states.\n");
    }
    printf("\nAll tests done for playAdventurer!\n");
    return 0;
}