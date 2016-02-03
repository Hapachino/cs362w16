**** If you are having trouble compiling, run "make clean", then run "make unittestresults.out" ****
**** You will get two outputs... unittestresults.out & unittestresultsrobust.out. ******************
**** The second includes all test case returns from the test runs... it is very long ***************
**** I don't mention bugs here because they are all covered in bug1.c ******************************

File 'dominion.c'
Lines executed: 41.84% of 588
Branches executed: 48.92% of 415
Taken at least once: 42.17% of 415
Calls executed: 22.77% of 101
dominion.c:creating 'dominion.c.gcov'

The line executed % does not surprise me, given the lack of cards covered. 
There are over 27 cards (~24 playable), and we only created code coverage 
for 4 of them

Branches executed: taken the same logic applies. However, a lot of branches are covered 
in the game initializer, which was used extensively by my test cases. Most of 
these branches are hit given my test cases, but I will comment on how this is 
misleading later on.

Taken at least once: This make sense to me, because the initializer seemed to be working. 
This was one of the largest lines of code that had several error catching statement built
into it. None of these ever seemed to be tripped (my tests were designed to catch them), so
I don't believe these branches would have ever been reached. This also is a result of the 
cardEffect branches. The cardEffect call was used for one of the testCases, and numerous 
branches will be evaluated but not explored depending on what is passed in.

Calls executed: Since we were only testing 4 units, and 4 cards, I'm not surprised by the 
lack of call coverage. To get complete call coverage we would need to be testing every single 
item in the system directly. Clearly this shows that the majority of lines exist in a few helper 
functions and/or the units I decided to test. Helper functions like initialize deck, draw cards, 
and other items that were used seem to have longer code blocks than what was left behind. This is
how the system was able to get substantially higher lines covered instead of calls. 

cardtest Overview: All card test randomized the player that was currently playing, the cards in 
the players hand, and other factors. It also randomized the number of cards in the users hand, to 
ensure that numerous combinations of cards were attempted.

cardtest1: 
Primary function: playSmithy 
Ancillary functions: drawCard, discardCard, initializeGame
The primary function to be covered by this was playSmithy, and every branch and option within 
Smithy was sufficiently covered. The only variation that could have been made is potentially 
adding more variety to the call to discardCard that Smithy makes, but that code should be 
tested signficantly on its own instead.

cardtest2:
Primary function: playAdventurer
Ancillary functions: initializeGame, shuffle, drawCard
The primary function to be covered by this was playAdventurer, and every branch and option within 
Adventurer was sufficiently covered. There were several branches that were covered less than others, 
but this was to be expected. These branches were the end of while loops, or if statements when treasures 
were found, which treasures statistically make up about 3/27ths of the average hand, which fell in line within
expectations for the test. 

cardtest3:
Primary function: outpost switch statement
Ancillary functions: initializeGame, discardCard, cardEffect
The primary function to be covered by this was outpost card in cardEffect switch statement, and every statement 
in outpost was easily covered. There is not a lot of variation to the outpost card, and it's actually more interesting
to focus on what is handled next by outpost in regards to which player gets their turn next. However, this action, so
is outside the scope of this test.

cardtest4:
Primary function: playVillage
Ancillary functions: discardCard, initializeGame
The primary function to be covered by this was the playVillage card, which had every statement sufficiently covered. 
There is no branching in the playVillage refractored code, and two external calls, both of which were called in every
single test case. 

unittest Overview: 
Most of these unit tests relied on random assignment of cards, within paramenters that were guanranteed to form interesting
combinations of cards a substantial amount of the time. 

unittest1:
Primary function: isGameOver()
Ancillary functions: initializeGame
The primary function to be covered by this was the isGameOver function, which had every statement sufficiently covered. 
There are a lot of branches in this function, so I wanted to make sure that all branches were covered, which they were.
Some obviously had a higher percentage of being taken becuase they are for loops, or because some if statements are the 
error case or exit case when a condition is met. I randomized the input cars so that they would be guaranteed to 
occasionally trigger the end of the game. The end of the game was also often not returned becuase of a bug in the code.

unittest2:
Primary function: getCost()
Ancillary functions: initializeGame
The primary function to be covered by this was the getCost function, which had every statement sufficiently covered. 
There are a lot of branches in this function, so I wanted to make sure that all branches were covered, which they were.
Some obviously had a higher percentage of being taken becuase they are for loops, or because some if statements are the 
error case or exit case when a condition is met. I randomized the input cars so that they would be guaranteed to 
occasionally trigger the end of the game. The end of the game was also often not returned becuase of a bug in the code.

unittest3:
Primary function: updateCoins()
Ancillary functions: initializeGame
The primary function to be covered by this was the updateCoins function, which had every branch/statement sufficiently covered. 
I wanted to input randomly generated sets of coins that covered all possible cases, along with random bonus point amounts. 
This resulted in all branches being sufficiently covered, and the for loop being run through multiple times. Sometimes with 
exiting immediately.

unittest4:
Primary function: scoreFor()
Ancillary functions: initializeGame
The primary function to be covered by this was the scoreFor function, which had every branch/statement sufficiently covered. 
The primary concern here is that all applicable test cards were generated, so that every branch and statement would be covered 
in a random fashion. It also required that the hand, discard, and deck all have cards in different combinations to this. My test 
was sure to randomize these items to ensure that everything was covered sufficiently. You will see that the times a branch was taken
is very low, but that is because I randomly generated decks of cards using the 27 cards, yet only 6 were valid for scoring. 

General Comments:

The coverage shows that I'm covering the game initializer, discardCard, cardEffect, drawCard, and shuffle. While this is true, 
I'm never actually testing all bounds of these functions. As such, code coverage % can be misleading because a large majority
of my coverage is on areas I'm not actaully testing. This also applies to any ancillary functions covered by the functions I direclty
called that I'm not explicitly using.could be misleading in the real world, as development teams just shoot to get 100% code coverage, 
but might not do it in a useful fashion.