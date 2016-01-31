#include "test_helper.h"
#include "rngs.h"
#include <math.h>
#include "dominion.h"
#include <stdio.h>

void printHand(struct gameState *game){
    int currentPlayer = whoseTurn(game);

    for (int i = 0; i < game->handCount[currentPlayer]; i++)
        printf("Hand[%d]: %d\n", i, game->hand[currentPlayer][i]);

return;

}

void printDeck(struct gameState *game){
    int currentPlayer = whoseTurn(game);

    for (int i = 0; i < game->deckCount[currentPlayer]; i++)
        printf("Deck[%d]: %d\n", i, game->deck[currentPlayer][i]);

    return;

}
int flagCheck(int testState, int validFlag)
{
    if (testState == -1 && validFlag == 1)
        return -1;
    else if (testState == 1 && validFlag == 1)
        return 1;
    else if (testState == -1 && validFlag == -1)
        return 1;
    else if (testState == 1 && validFlag == -1)
        return -1;

    return 0;

}

void resetGameState(struct gameState *Game)
{
    int i, j;

    Game->numPlayers = 0;
    for (i = 0; i < treasure_map+1; i++){
        Game->supplyCount[i] = 0;
        Game->embargoTokens[i] = 0;
    }
    Game->outpostPlayed = 0;
    Game->outpostTurn = 0;
    Game->whoseTurn = 0;
    Game->phase = 0;
    Game->numActions = 0;
    Game->coins = 0;
    Game->numBuys = 0;
    for (i = 0; i < MAX_PLAYERS; i++){
        for (j = 0; j < MAX_HAND; j++)
            Game->hand[i][j] = 0;
        
        Game->handCount[i] = 0;
        for (j = 0; j < MAX_DECK; j++){
            Game->deck[i][j] = 0;
            Game->discard[i][j] = 0;
        }

        Game->deckCount[i] = 0;
        Game->discardCount[i] = 0;
    }
    for (i = 0; i < MAX_DECK; i++)
        Game->playedCards[i] = 0;

    Game->playedCardCount = 0;

    return;
}        
void randomizeKingdomCards(int k[10])
{

    int i, j, temp;
    double dtemp;

    for (i = 0; i < 10; i++)
    {
        k[i] = -1;
        while(k[i] == -1)
        {
            temp =(int) ((Random() * (27 - 8) + 8));
            for (j = 0; j < i; j++){
                if (k[j] == temp){
                    temp = 0;
                    break;
                    }
            }
            if (temp != 0)
                k[i] = temp;
            }
    }


    return;
}

void printGame(struct gameState control)
{
    int i, j;
    
    printf("numPlayers:\t%d\n", control.numPlayers);
    printf("supplyCount:\n");
    for (i = 0; i <= treasure_map; i++){
        printf("\t\t%d", control.supplyCount[i]);
        ((i%4) == 0) ? printf("\n") : printf("");
    }
    printf("\n");

    printf("embargoTokens:\n");
    for (i = 0; i <= treasure_map; i++){
        printf("\t\t%d", control.embargoTokens[i]);
        ((i%4) == 0) ? printf("\n") : printf(" ");
        }
    printf("\n");
    printf("outpostPlayed:\t%d\n", control.outpostPlayed);
    printf("Whose Turn:\t%d\n", control.whoseTurn);
    printf("Phase: \t\t%d\n", control.phase);
    printf("numActions: \t%d\n", control.numActions);
    printf("coins:\t\t%d\n", control.coins);
    printf("numBuys:\t%d\n", control.numBuys);
    printf("hand:\t\t\n");
    for (i = 0; i < control.numPlayers; i++){
        for (j = 0; j < control.handCount[i]; j++){
            printf("\t\t%d", control.hand[i][j]);
            ((j % 4)== 0) ? printf("\n") : printf(" ");
        }
        printf("\n--------------------------------\n");
    }
    printf("\n");

    printf("handCount: \t\n");
    for (i = 0; i < control.numPlayers; i++){
        printf("\t\t%d", control.handCount[i]);
        ((i % 4) == 0) ? printf("\n") : printf(" ");
    }
    printf("\n");

    printf("deck:\t\t\n");
    for (i = 0; i < control.numPlayers; i++){
        for (j = 0; j < control.deckCount[i]; j++){
            printf("\t\t%d", control.deck[i][j]);
            ((j%4) == 0) ? printf("\n") : printf(" ");
        }
        printf("\n----------------------------------\n");
    }

    printf("");
    printf("deckCount:\t\n");
    for (i = 0; i < control.numPlayers; i++){
        printf("\t\t%d", control.deckCount[i]);
        ((i % 4) == 0) ? printf("\n") : printf(" ");
    }
    printf("\n");
    printf("discard:\t\n");
    for (i = 0; i < control.numPlayers; i++){
        for(j = 0; j < control.discardCount[i]; j++){
            printf("\t\t%d", control.discard[i][j]);
            ((j % 4) == 0) ? printf("\n") : printf(" ");
        }
        printf("\n-----------------------------------\n");
    }

    printf("\n");
    printf("discardCount:\t\n");
    for (i = 0; i < control.numPlayers; i++){
        printf("\t\t%d", control.discardCount[i]);
        ((i % 4) == 0) ? printf("\n") : printf(" ");
    }

    printf("\n");
    printf("playedCards:\t\n");
    for (i = 0; i < control.playedCardCount; i++){
        printf("\t\t%d", control.playedCards[i]);
        ((i % 4) == 0)? printf("\n") : printf(" ");

        }
    printf("playedCardCount:%d\t\n", control.playedCardCount);

    return;



}

