Robyn Lin
Assignment 5
BugsInTeammates.c

staplest tests:
-Smithy card: 1 bug
Bug 1: actual handcount after playing smithy was one more than the expected handcount
Description: Test the handcount before and after calling smithy.  The handcount will be off by 1 card.
Steps to reproduce: See cardtest1
Note: This is probably the bug you introduced

-Adventurer card: worked correctly

-Village card: 1 bug
Bug 1: actual number of actions after playing village was 1 more than the expected number of actions
Description: Test the handcount and number of actions before and after calling village. The number of actions will be 
off by 1.
Steps to reproduce: See cardtest3
Note: may be a bug introduced in original file dominion.c

-Great Hall card: 1 bug
Bug 1: actual number of actions after playing great hall was 1 more than the expected number of actions
Description: Test the handcount and number of actions before and after calling great hall. The number of actions will be 
off by 1.
Steps to reproduce: See cardtest4
Note: may be a bug introduced in original file dominion.c

-shuffle() function: works correctly

-updateCoins() function: works correctly

-scoreFor() function: 1 bug
Bug 1: score calculated by scoreFor() function in dominion.c doesn't equal the score manually calculated in this unit test.
Description: manually add score in testScoreFor() function
Steps to reproduce: See unittest3
Note: may be a bug introduced in original file dominion.c

-isGameOver() function: works correctly

yaof:
-Smithy card: 1 bug
Bug 1: actual handcount after playing smithy was one more than the expected handcount
Description: Test the handcount before and after calling smithy.  The handcount will be off by 1 card.
Steps to reproduce: See cardtest1
Note: This is the bug you introduced

-Adventurer card: works correctly

-Village card: 1 bug
Bug 1: actual number of actions after playing village was 1 more than the expected number of actions
Description: Test the handcount and number of actions before and after calling village. The number of actions will be 
off by 1.
Steps to reproduce: See cardtest3
Note: may be a bug introduced in original file dominion.c

-Great Hall card: 1 bug
Bug 1: actual number of actions after playing great hall was 1 more than the expected number of actions
Description: Test the handcount and number of actions before and after calling great hall. The number of actions will be 
off by 1.
Steps to reproduce: See cardtest4
Note: may be a bug introduced in original file dominion.c

-shuffle() function: works correctly

-updateCoins() function: works correctly

-scoreFor() function: 1 bug
Bug 1: score calculated by scoreFor() function in dominion.c doesn't equal the score manually calculated in this unit test.
Description: manually add score in testScoreFor() function
Steps to reproduce: See unittest3
Note: may be a bug introduced in original file dominion.c

-isGameOver() function: works correctly
