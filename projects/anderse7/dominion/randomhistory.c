/*****************************************************************************
Author: Eric Anderson
Assignment: 4, random testing
Purpose: Discuss development of random testers, improvements in coverage, and
effort to check the correctness of specification
*****************************************************************************/

/*
randomtestcard.c : Testing the Smithy Card

Development of the random tester -
I chose this card because I wantewd a direct comparison of random testing vs. fixed testing.

I tested the same +3 card scenarios as I did in the first test, then I added a lot more 
tests to determine how other players were effected as well (deck size and hand counts, 
if the smithy card landed in the right pile and as looking at supply piles etc.

Improvements in Coverage -

Previous coverage with fixed test

File 'cardtest2.c'
Lines executed:73.27% of 101
Branches executed:100.00% of 32
Taken at least once:65.62% of 32
No calls

Coverage with random test

File 'randomtestcard.c'
Lines executed:84.13% of 63
Branches executed:100.00% of 28
Taken at least once:64.29% of 28
No calls

The coverage was slightly better but by looking at the gcov file, this is reflected in 
there being more lines of code in this version.  Every line was executed as in the 
first version.  The big difference was in the number of times they were executed. 
Originally I looped 2000 times on the card.  This results in a much longer time to 
run and much more output.  I knocked this back to 20 times for your benefit!

In the previous fixed test, I discovered something wrong with the handcount.  
I determined to do better coverage and randomize things.  It is clear that there is 
an issue with the handcount.  It is off by one.  The random test also revealed that 
there is an issue with the handsize of the other players.  This requires additional 
testing! The player's pile and the played pile are also incorrect.  I believe 
these are the result of the bug I introduced to the game.  The interesting thing 
here is that with random testing, I discovered far more issues with the Smithy 
card compared to the first set of tests.

On the positive side of testing, I have been able to verify that the supply counts 
seem pass every time using both test methods.  My confidence in this area is high.

randomtestadventurer.c : Testing the Adventurer Card

Development of the random tester -
As discussed in the lecture, sending completely random test values is of little use for 
a function that expects a valid game state. So, I began development of the testor by 
identifying a valid game state.

For starters, I idenfitied what needed to be randomized prior to initializing the
game state. For me, this was the number of players and the kingdom cards. 

Since we were not testing the entire game, just the adventurer card, I focused on the 
maximum number of players (I also tested the minimum number of players for bounds checking), 
My first attempt at designing this test failed, because it uses the shuffle function to 
randomize its results. I learned that by using PutSeed with a sync value I could ensure 
identical results between my pre and post game states. This allowed me to complete the 
test sequence. 

After initializing the game, I randomzed elements within the game state prior to
running the function under test. The elements that I felt were key to randomize were
the decksize, the hand size, and the position of the adventurer card.

In addition to testing the coins (the obvious test), I tested around the primary player to 
see what side effects may result.  I tested with a contrived hand,  set the deck count to 
0 (a bounds test) and then inspected other players hands for side effects. 

I randomized which treasure cards they were as well as their position within the deck. I 
felt that in doing this I was achieving solid coverage against some game states that 
might occur in the purely random tester that may not be valid.

Improvements in Coverage -
You can see from these test results that I covered much more of the code and like the 
randomtestcard got better coverage and results. I chose to print the data for each of 
the randomized elements prior to running the tests. I did see a failure in the coin 
count test.The test failed because the amount I expected was not possible. I saw this 
in scenarios where I expected a number and that "expected" number, due to the formula, 
ended up being negative. That is, of course, not possible and the test, actually doesn't 
show a fault.

General Coverage Comments -

Previous coverage with fixed test

Function 'playAdventurer'
Lines executed:53.33% of 15
Branches executed:66.67% of 12
Taken at least once:41.67% of 12
No calls

Coverage with random test

Function 'playAdventurer'
Lines executed:100.00% of 15
Branches executed:100.00% of 12
Taken at least once:91.67% of 12
No calls

You can see from these dramatic changes in test results, test covered much more of the 
code and like the randomtestcard got better coverage and results.

OVERALL COVERAGE -
overall coverage of dominion.c with eight tests was
File 'dominion.c'
Lines executed:34.30% of 653
Branches executed:36.04% of 419
Taken at least once:28.64% of 419
No calls

this is better than the results of just two tests
File 'dominion.c'
Lines executed:14.55% of 653
Branches executed:14.56% of 419
Taken at least once:9.07% of 419
No calls
 But by linear math, if I were to add six more tests, I'd land in the roughly 60% coverage range. 
 clearly the random tests are yielding better results.
*/
