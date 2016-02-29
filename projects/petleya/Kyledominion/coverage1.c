/*
Kyle Johnson
CS362
Assignment 3
coverage1.c

Results from gcov:

File 'dominion.c'
Lines executed:32.87% of 575
Branches executed:32.37% of 417
Taken at least once:23.74% of 417
Calls executed:25.26% of 95

While the coverage percentages are relatively low, this is not unexpected since only 4 functions
and 4 cards were being tested.  The lowest coverage was for the branches taken at least once, at 24%.
This indicates that my testing scenarios were too narrow and I missed the outlier and more fringe
scenarios.  This could be improved by both increasing the scope of the random testing elements, and implementing
more carefully constructed scenarios meant to trigger a wider variety of paths so that more cases are
explored at least once.

While the functions and cards I tested had returned 100% blocks executed 100%, the branch coverage was
much lower.  with updateCoins, for example:

function updateCoins called 444 returned 100% blocks executed 100%
444: 1404:int updateCoins(int player, struct gameState *state, int bonus)
        -: 1405:{
        -: 1406:  int i;
        -: 1407:	
        -: 1408:  //reset coin count
      444: 1409:  state->coins = 0;
        -: 1410:
        -: 1411:  //add coins for each Treasure card in player's hand
     2004: 1412:  for (i = 0; i < state->handCount[player]; i++)
branch  0 taken 78%
branch  1 taken 22% (fallthrough)
        -: 1413:    {
     1560: 1414:      if (state->hand[player][i] == copper)
branch  0 taken 50% (fallthrough)
branch  1 taken 50%
        -: 1415:	{
      786: 1416:	  state->coins += 1;
        -: 1417:	}
      774: 1418:      else if (state->hand[player][i] == silver)
branch  0 taken 43% (fallthrough)
branch  1 taken 57%
        -: 1419:	{
      330: 1420:	  state->coins += 2;
        -: 1421:	}
      444: 1422:      else if (state->hand[player][i] == gold)
branch  0 taken 74% (fallthrough)
branch  1 taken 26%

This shows that my test was weaker for many of the branch 1 fallthroughs.  Reviewing the results from
gcov make it easier to plan for more expansive coverage by seeing which branches within the function
were active the least.  Given more time, I would focus on the lower percentage branches within the functions
to increase the overall test coverage.

*/
