Analysis of the dominion code coverage

Testing completed
File 'dominion.c'
Lines executed:43.01% of 565
Branches executed:35.01% of 417
Taken at least once:31.41% of 417
Calls executed:31.00% of 100

After analysis of the dominion.c code coverage, I can see that the coverage of my 
tests were fine. The executed lines and/or branches were not 100% since not every
function was tested by my unit tests.
 
function buyCard called 82 returned 100% blocks executed 100%
function isGameOver called 205 returned 100% blocks executed 100%
function getCost called 229 returned 100% blocks executed 100%
function updateCoins called 589 returned 100% blocks executed 100%
function playAdventurer called 350 returned 100% blocks executed 100%
function playSmithy called 200 returned 100% blocks executed 100%
function playVillage called 200 returned 100% blocks executed 100%
function playSalvager called 200 returned 100% blocks executed 100%

All of my tested functions returned 100% coverage. After completing my testing,
I noticed that there are many other test cases that could be implemented to 
further test the correctness of the code. For example, for all of my tests,
I hard coded starting values and set the number of players equal to 2. I 
started using random input, can be seen in isGameOver and buyCard unit tests.
This led me see a bug in isGameOver since setting 3 piles to 0 did not always
pass the unit test. For the card tests, more specific and intricate tests
can be tested. For my functions, only some of the player's game state
changes were monitored. My boundary testing can be improved. I saw the importance
of boundary testing specifically for the isGameOver function. The function did not
take into account sea_hag and treasure_map, which were 25 and 26 in the supply pile
index. Because I tested for the boundary, I was able to detect the bug. For future
test suites, I would definitely concentrate on the random input as this led me
to see bugs that I have not considered for testing and boundary testing as these
tests ensured that all of the function and all of the input that can be used has
been tested.