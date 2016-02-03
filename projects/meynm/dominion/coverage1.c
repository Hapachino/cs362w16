/*
coverage1.c
Matthew Meyn
2016/2/2

Coverage of dominion.c

File 'dominion.c'
Lines executed:42.20% of 519
Branches executed:37.06% of 367
Taken at least once:34.60% of 367
Calls executed:21.92% of 73

Over all, we see that less than half the lines in dominion.c were executed, with a little over a 
third of all branches having been taken. It is not surprising that coverage of dominion.c was 
relatively sparse, since there are many parts of the program that were not tested. Some functions,
like kingdomCards and newGame, are not used at all, in fact, I am not sure they are used by any 
part of the project in its ordinary form. There are some small utility functions like numHandCards
and handCard that are often not used by the main driver code because it is possible to simply 
access the data structures directly.

Another function that is not used at all is playCard. This makes sense because I did not choose 
this as one of my unit tests, and the card tests all call card functions directly, so playCard is
not used. The functions getWinners, isGameOver and scoreFor are also not covered, because they are 
not in the unit tests, and we are not testing a complete game. There are a few kingdom cards that 
call isGameOver, but none of these are among my card tests. There is no coverage of cardEffect, 
because it is not in the unit tests, and we are calling the card functions directly in the card 
tests.

Not surprisingly, initializeGame is covered pretty heavily, since we initialize a lot of games to 
run our tests. The loop that validates that the specified kingdom cards are all unique gets a lot
of use, as you would expect of an O(n^2) operation. The code the sets the kingdom cards is run many
times as well.

I will consider in particular detail buyCard, shuffle, gainCard, and fullDeckCount since these are 
the 4 functions targeted by my unit tests. buyCard was called 484146 times, with 100% of blocks 
executed. There are several branches in this function. In 

						if (state->numBuys < 1)
						
the first branch was taken 17 percent of the time, the second 83 percent. In

						else if (supplyCount( supplyPos, state ) < 1)

the first branch was taken only 1 percent of the time, presumably because most of the time the 
supply of whatever card was requested was not exhausted. Out of about 242,000 calls, it appears 
that a little over 200,000 times the function returns -1. Most of these negative return values
came from 

						if (state->coins < getCost( supplyPos )

In other words, the player did not have enough coins most of the time. A value of 0 was returned
about 40,000 times. So, apparently, my tests that involved buyCard were testing a lot of situations
in which invalid input was being provided to the function. This makes sense, because I used random
testing on this particular function, and probably most of the combinations of values were expected
not to succeed. This seems a reasonable result, because we want to be sure to cover boundary cases
where we test that the game's rules are enforced properly.

The shuffle function was called about 837,000 times. From the statement

						if (state->deckCount[player] < 1)
						
the first branch is taken only 1% of the time. This is because our unit tests are mostly quite
abbreviated. We don't play a whole game, we just call a function once, which means we are unlikely
to exhaust a player's deck very often. This is what the coverage data show. It would probably be
a good idea to improve coverage of this case where the deck contains no cards, since this happened
apparently only 4 times. This could be an important boundary case, so we should test it.

The coverage shows gainCard being called about 73,000 times. When gainCard tests to see if the 
supply of the card to be gained,

						if (supplyCount( supplyPos, state ) < 1)

the first branch is taken 39% of the time, resulting in a return of -1. This seems a reasonable 
coverage of the boundary case. However, the value of toFlag (showing where the new card should go)
is very heavily distributed toward "else", which is to say, something that is not 1 or 2. This 
means "add to discard", but the card can also be added to the deck or hand. These cases should 
really be covered, so it would be a good idea to try to find functions that will call gainCard with
a toFlag value of 1 or 2, or to call it directly with those values.

fullDeckCount was called 600,000 times. There is not much of interest in the branch coverage here, 
because the branches are basically loops counting various cards. Over all, the coverage of this 
function looks quite even. This is not surprising, as this is a pretty simple function without many
possible paths through the code.

Some other functions were called a substantial number of times. Branch coverage shows endTurn being
called about 225,000 times, probably because I used it quite a bit in my card tests to allow me to 
use various players to test those functions. The line

							state->whoseTurn = 0; 

is the only one that never executes. This is because the line is supposed to happen if it is the 
last player's turn, so the turn returns to the first player. This doesn't happen in my tests 
because we never go through more than one turn.

Another function that was called frequently was drawCard. This makes sense, because many of the 
card functions involve drawing one or more cards. The branch that corresponds to an empty deck is
covered very little, presumably because a game state is not used enough before re-initializing.
It would probably be a good idea to try to cover this case more. 

getCost is covered a good deal, although it is not a very interesting or complex function. It is 
basically a long switch-case statement.

discardCard is covered somewhat, probably because it is used in some of the card functions. The 
case where there is only one card in the player's hand is not covered at all, so that would be a 
good edge case to cover at least a few times. Otherwise, coverage looks pretty complete in this
function.

Finally, updateCoins is called fairly frequently. It is a simple function, and each branch gets 
some coverage. 
						
						
						
						