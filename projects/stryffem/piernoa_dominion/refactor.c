Cards moved into their own functions:
  Adventurer:
    - shuffle(currentPlayer - 1, state); istead of shuffle(currentPlayer, state);
    - cardDrawn = state->hand[currentPlayer - 1 ][state->handCount[currentPlayer]-1]; instead of cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1];
    - if (cardDrawn == copper && cardDrawn == silver || cardDrawn == gold) instead of         if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
    - state->handCount[currentPlayer]; instead of state->handCount[currentPlayer]--;
    - while(z-1<=0) instaed of while(z-1>=0)

  Smithy:
    - drawCard(currentPlayer - 1, state); instead of drawCard(currentPlayer, state);
    - discardCard(handPos, currentPlayer, state, 1); instead of discardCard(handPos, currentPlayer, state, 0);

  Feast:
    - if (nextPlayer < (state->numPlayers - 1)) instead  of if (nextPlayer > (state->numPlayers - 1))
    - deleted line instead of   temphand[i] = state->hand[currentPlayer][i];//Backup card

  Council Room:
    - for (i = 4; i > 0; i++) instead of for (i = 0; i < 4; i++)
    - drawCard(i, state); drawCard(i, state); instead of drawCard(i, state);

  Gardens:
    returns 0 instead of -1;

  Mine:
    - if (state->hand[currentPlayer][choice1] < gold || state->hand[currentPlayer][choice1] > copper)  instead of if (state->hand[currentPlayer][choice1] < copper || state->hand[currentPlayer][choice1] > gold)
    - if (choice2 > treasure_map && choice2 < curse) instaed of if (choice2 > treasure_map || choice2 < curse)


Notes from assignment III.

While no new bugs were introduced, I did make two versions of the funcitons I tested and introduced bugs to.
For example, there are two smithy funcitons, one with bugs I introduced, and one without. 
