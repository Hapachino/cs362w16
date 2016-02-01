Overall, my total statement coverage was 32.07% and my total branch coverage was 41.23%. I think that these results are quite reasonable considering the 
relatively small subset of the program that I have tested so far.  The individual coverage for functions varied. Of course, the functions that I tested had 
higher coverage.  For the most part, functions that I did not explicitly test had little to no coverage. However, many functions that I did not explicitly 
test had high coverage because dominion.c includes many functions calling other function during execution.  For example, I did not explicitly test the whoseTurn() 
function, but I achieved 100% statement coverage because during the course of a game, this function is implicitly called several times.  This is another reason 
why testing this particular program can be complex because a bug that may be found during the testing of one function may actually originate from another related 
function. I particularly noticed that I need to expand my test suite in the future to explicitly test the following functions because these functions had relatively
low coverage: playCard, buyCard, numHandCards, handCard, endTurn, isGameOver, scoreFor, getWinners.  Most of these functions are associated with moving to the next 
turn or ending the game.   I never allowed my tests to get past one or two turns. Therefore, it makes sense that these functions had low coverage. In the future, to 
adequately cover these function I will have to write a test that will allow the game to run until completion.  

I found that all of the functions that I tested had relatively high statement coverage and branch coverages of 75-100%, except for drawCard.  This is partly due 
to the DEBUG statements already present in the function. For obvious reasons, these will not execute.  However, I noticed after reviewing the gcda file that even 
when I pass the function an empty deck, it does not shuffle as expected (therefore, many statements that depend on this fact don’t execute). I’m not sure if this 
is a bug or just an error in my boundary testing strategy. Therefore, I didn’t report it. I think if I could figure out why this is happening, then I could increase 
the coverage to a more acceptable rate.  As far as the card implementations, I achieved 100% coverage for smithy and council room. However, I had some lower coverage 
amounts for adventurer (64%).  The lower coverage for the adventurer card seems to be caused by something I overlooked when I designed my test.  The adventurer card
allows the player to draw card until three treasure cards are drawn.  I did not stack the deck in my test design.  I let the program stack the deck.  Apparently, 
because of this, the deck has three treasure cards on top. So, the function never executes the line that throws away non-treasure cards and allows the player to draw
again. I can fix this in he future by stacking the deck before playing the adventurer card with some treasure cards and some non-treasure cards on top to give more 
coverage to those sections of the function.
