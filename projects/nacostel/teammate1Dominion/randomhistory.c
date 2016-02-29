I chose to create random testers for the smithy card and the required adventurer card. I previously tested these cards in assignment 3. I tested the same aspects of each card that I tested in 
assignment 3: current player's hand count, whether the played card is discarded correctly, the current player's deck count, the other player's hand count, and the other player's deck count.
In addition, for the adventurer card, I tested whether the last two cards drawn were treasure cards.  For each tester, I tested the specified card 1000 times.  The basic process for each 
random tester was very similar: randomly assign bytes to the game state then limit the values for certain aspects of the game state to avoid segmentation faults for outrageous values.  For example, 
I limited the hand count for each player to be a random number between 1 and the MAX_HAND constant.  At the end of all 1000 tests, I printed the number of failures for each test.

Even though I tested the same aspects of each card that I tested in assignment 3, I saw improvements in coverage.  In assignment 3, my total statement coverage was 32.07% and my total branch coverage 
was 41.23%.  To determine the additional coverage that my random testers provide, I ran all 8 tests from assignment 3 and the additional random testers and found the coverage for all 10 tests.  Both 
the statement and branch coverage increased. The new statement coverage was  36.38% and the new branch coverage was 43.13%.  I had previously achieved 100% statement coverage for the smithy card in 
assignment 3 and I matched this same level of coverage in assignment 4.  However, in assignment 3, I only achieved 64% statement coverage for the adventurer card.  I suspected at the time that this
was due to the cards in the player's hand not being assigned randomly enough. It seems that my suspicions were true because my random tester for the adventurer card achieved 100% coverage. Due to 
these results, I think that I have thoroughly tested both the smithy and adventurer cards. In the future, to improve my test suite, I need to test other cards/functions thoroughly to improve overall
statement and branch coverage more substantially.