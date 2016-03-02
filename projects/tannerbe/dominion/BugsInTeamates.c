whitegr:

-Smithy card draws an extra card, shown by cardtest1
-Adventurer card does not get added to played cards pile after being played, shown by cardtest2 and randomtestadventurer
-Embargo card adds coins to player even if selected pile for adding the embargo token is invalid, shown by randomtestcard


konopaz:

-Village Card: assertion on post cardEffect handCount fails because it is not one less than the pre cardEffect. Assertions on
the playedCardCount, and the last playedCard also fail because of the same reason.
-Adventurer card does not get added to played cards pile after being played, shown by cardtest2 and randomtestadventurer
-Adventurer card modifies parts of the game that it should not, shown by memcmp in cardtest2.
-Embargo card adds coins to player even if selected pile for adding the embargo token is invalid, shown by randomtestcard

Note: according to your refactor.c, you added a bug in smithy that pre increments i instead of post increments i. This doesn't 
actually cause a bug in the functionality of the smithy card because the loop still runs three times.
