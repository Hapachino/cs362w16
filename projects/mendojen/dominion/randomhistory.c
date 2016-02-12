Jennifer Mendoza
Description of Random test development
Results can be obtained by running make randomtestadventurer.out and make randomtestcard.out

Initial Stages of Development
I concentrated on what I tested for in Assigment 3. I also kept track of the bugs that I found with the fixed tests to 
effectively create random tests. I also based my tests on Assignment 3. The difference would be the random inputs
and increased complexity by checking more members of the game state of each player. 

randomtestcard.c (Smithy Card)
I used testDrawCard.c as a template on my random card test. The overall structure of my program includes a main
function which calls testSmithy, a function I defined in the program. I wanted this test to test more members
of the game state for both player 1 and player 2. I initially tested for hand count, discard count, and deck count 
for both players and kept track of any changes by using memcpy. For my final submission, I added more members to 
test for to account for all the members that should/should not have changed when playSmithy was called.

randomtestadventurer.c (Adventurer Card)
Similar to the randomtestcard.c file, I again used testDrawCard.c as a template for my tests. I looked at my previous 
assignment and used the same structure for this assignment. I used the code I had for randomtestcard.c and just added 
more tests to check for more gamestate members. For my final submission, my additions should account for all the 
members that should/should not have changed when playAdventurer was called.




Coverage Analysis:
With my first check at my coverage, the coverage for assignment 3 is higher than assignment 4. I concentrated on 
improving my random test to get a higher coverage. I was able to cover more tests, but my percentages were nearly
identical. I looked at the branch coverage to see how my code can be improved. I improved my Adventurer card test
as my random tests gave me a coverage of 62%. I included my fixed tests and was able to obtain 100%. Lines executed
improved while the other stats almost stayed the same. I added more tests and more complexity in the test which puzzled
me a bit on why my coverage did not improve. I was able to increase the percentages when looking at the coverage data.
I included the scenario that would invoke the specific branch. However, this only increased my percentage by a fraction
of a percent.

Previous Smithy card coverage
Lines executed:24.42% of 565
Branches executed:20.14% of 417
Taken at least once:16.55% of 417
Calls executed:14.00% of 100
function playSmithy called 200 returned 100% blocks executed 100%

Previous Adventurer card coverage
Lines executed:25.31% of 565
Branches executed:21.10% of 417
Taken at least once:17.99% of 417
Calls executed:14.00% of 100
function playAdventurer called 350 returned 100% blocks executed 100%

Updated Smithy card coverage
Lines executed:26.19% of 565
Branches executed:20.14% of 417
Taken at least once:15.83% of 417
Calls executed:14.00% of 100
function playSmithy called 2000 returned 100% blocks executed 100%


Updated Adventurer card coverage
Lines executed:28.85% of 565
Branches executed:21.58% of 417
Taken at least once:18.94% of 417
Calls executed:14.00% of 100
function playAdventurer called 2350 returned 100% blocks executed 100%