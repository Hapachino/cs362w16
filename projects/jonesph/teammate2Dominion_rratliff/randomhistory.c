/*

random test adventurer

1. Identify the interface to test
   The adventurer card was refactored into cardEffectAdventurer() and called
   directly by the random test. The current player number and the gate state.

2. Write code to generate random inputs
   Game initialization was the biggest challenge. Used the definitions in 
   dominion.h for MAX_PLAYERS, MAX_HAND and MAX_DECK with Random() to setup
   the card piles. Randomly populated card piles with cards. Created an 
   array for treasure cards in the manner of kingdom cards. Biased the 
   deck toward kingdom cards instead of treasure cards to cause more code
   iterations. Always made sure there were two players.

3. Write code to check behavior - did it work
   Oracle code written with "business rules" of the adventurer card and
   results comparison. The gate state was copied and the oracle code operated
   on it. The adventurer card operated on the original game state. The two 
   were compared afterward. A while loop was re-written that originally from
   zero and up but there were too many and inconsistent failures. The reason
   was the adventurer card started at the highest position and counted down.
   The bug in the discard function is evident in the results. Discard count
   consistently failes.

4. Gather code coverage
   All important code is covered. shuffle() call was avoided because the tests
   would be non-deterministic after a shuffle. There are some branches taken
   less often but these are understandable such as being in the while loop
   more often than falling through searching for treasure cards.

   Function 'cardEffectAdventurer'
   Lines executed:94.12% of 17
   Branches executed:100.00% of 12
   Taken at least once:91.67% of 12
   Calls executed:50.00% of 2

5. Adjust the code to generate inputs
   A bias was given toward kingdom cards over treasure cards so the deck 
   was operated on more often. MAX_HAND and MAX_DECK were used to provide
   more cards and operations over an original lower number (10). Iterations
   was increased from 1000 to 2000 to get more executions of lesser traveled
   branches.

6. Break the code to see if random tests detect the problem
   Code was broken to increase and decrease the number of treasure cards
   adventurer returns. The random tests caught both cases.

7. Improve oracle
   The oracle was improved as described above as code was tinkered with 
   to improve coverage and balance.

random test smithy

1. Identify the interface to test
   The smithy card was refactored into cardEffectSmithy() and called
   directly by the random test. The current player number, gate state,
   and hand position are in the interface.

2. Write code to generate random inputs
   Game initialization was again the biggest challenge but leveraged a lot
   from adventurer. Used MAX_PLAYERS, MAX_HAND and MAX_DECK with Random() 
   to setupu card piles. Randomly populated card piles with cards. Kept 
   the treasure card array and bias toward kingdom cards but that was 
   not important for smithy. Always made sure there were two players and
   a smithy card in first position.

3. Write code to check behavior - did it work
   Oracle code written with "business rules" of the smithy card and results
   comparison. The gate state was copied and the oracle code operated on the
   copy. The smithy card operated on the original game state. The two states
   were compared afterward. The bug in the discard function is evident in the 
   results. Discard count consistently failes. Hand and deck consistently 
   fails as well. This matches the bugs introducted during refactoring.

4. Gather code coverage
   All code is covered.  All lines and branches are executed.

   Function 'cardEffectSmithy'
   Lines executed:100.00% of 5
   Branches executed:100.00% of 2
   Taken at least once:100.00% of 2
   Calls executed:100.00% of 2

5. Adjust the code to generate inputs
   A bias was given toward kingdom cards over treasure cards but that was
   not really important for smithy. MAX_HAND and MAX_DECK were used to provide
   more cards and operations over an original lower number (10). Due to the 
   nature of smithy, number of iterations does not really improve coverage.

6. Break the code to see if random tests detect the problem
   Random tests have already caught the bugs introduced during refactoring.
   Further tweaks of those bugs were also caught, for example, smithy has
   a bug to draw 2 instead 3 cards. Random tests also catch drawing 4 instead
   of 3 cards.

7. Improve oracle
   The oracle was improved during check out of the fails which as it turned 
   out were introduced during refactoring.

*/
