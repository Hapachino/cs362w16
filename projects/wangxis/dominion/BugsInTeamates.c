Testing for teammate #1
Test adventurer card:
1.	Changes in my testing method:  Function name and parameters used to call the adventure card was changed to playAdventurer(post, p).
2.	Compiled with: gcc -o cardtest1 -g cardtest1.c  dominion.c rngs.c
3.	Bugs found: 
1)	Draw three treasure cards instead of two.
2)	Missing code that implements when deckCount == 0.
3)	Missing code that dumps the handCard just played. 
Test smithy card:
1.	Changes in my testing method: Function name and parameters uses  to call smithy card was changed to playSmithy(post, p, handPos);
2.	Compiled with:  gcc -o cardtest2 -g cardtest2.c  dominion.c rngs.c
3.	Bugs found: Discard the played card into trash pile instead of deck pile.
Test getCost() function: 
1.	Compiled with: gcc -o unittest1 -g unittest1.c  dominion.c rngs.c
2.	No bugs found.
Test isGameOver() function:
1.	Compiled with: gcc -o unittest2 -g unittest2.c  dominion.c rngs.c
2.	No bugs found.
Test scoreFor() function:
1.	Compiled with: gcc -o unittest3 -g unittest3.c  dominion.c rngs.c
2.	This function calls fullDeckCount() function which is implemented incorrectly. 
Test gainCard() function:
1.	Compiled with: gcc -o unittest4 -g unittest4.c  dominion.c rngs.c
2.	No bugs found.
Testing for teammate #2
Test adventurer card:
1.	Changes in my testing method:  Function name and parameters used to call the adventure card was changed to adventurerCard(p, post), remove the assertion for calling adventureCard() as it is a void function.
2.	Compiled with: gcc -o cardtest1 -g cardtest1.c  dominion.c rngs.c
3.	Bugs found: 
1)	Draw one treasure cards instead of two.
2)	Missing code that implements when deckCount == 0.
3)	Missing code that dumps the handCard just played. 
Test smithy card:
1.	Changes in my testing method: Function name and parameters uses  to call smithy card was changed to playSmithy(post, p, handPos);
2.	Compiled with:  gcc -o cardtest2 -g cardtest2.c  dominion.c rngs.c
3.	Bugs found: gain four cards instead of three.
Test results for getCost(), isGameOver(), scoreFor(), gainCard() are the same as the teammate #1.

