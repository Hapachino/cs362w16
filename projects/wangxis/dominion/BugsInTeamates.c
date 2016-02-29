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
Test feast card:
1.	Changes in my testing method:  Function name and parameters uses  to call feast card was changed to playFeast(post, p, supplyPos);
2.	Compiled with:  gcc -o cardtest3 -g cardtest3.c  dominion.c rngs.c
3.	Bugs found: There is infinite while loop
Test cutpurse ard:
1.	Changes in my testing method:  Function name and parameters uses  to call cutpurse card was changed to cardEffect(cutpurse,0,0,0,post,handPos,0);
2.	Compiled with:  gcc -o cardtest4 -g cardtest4.c  dominion.c rngs.c
3.	Bugs found: No bugs found.
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
Random test adventurer card:
1.	Changes in my testing method:  Function name and parameters used to call the adventure card was changed to playAdventurer(post, p).
2.	Compiled with: gcc -o randomtestadventurer -g randomtestadventurer.c  dominion.c rngs.c
3.	Bugs found: same as before.
Random test smithy card:
1.	Changes in my testing method: Function name and parameters uses  to call smithy card was changed to playSmithy(post, p, handPos);
2.	Compiled with:  gcc -o randomtestcard -g randomtestcard.c  dominion.c rngs.c
3.	Bugs found: Discard the played card into trash pile instead of deck pile

Testing for teammate #2
Test adventurer card:
1.	Changes in my testing method:  Function name and parameters used to call the adventure card was changed to adventurerCard(p, post), remove the assertion for calling adventureCard() as it is a void function.
2.	Compiled with: gcc -o cardtest1 -g cardtest1.c  dominion.c rngs.c
3.	Bugs found: 
1)	Draw one treasure cards instead of two.
2)	Missing code that implements when deckCount == 0.
3)	Missing code that dumps the handCard just played. 
Test smithy card:
1.	Changes in my testing method: Function name and parameters uses  to call smithy card was changed to smithyCard(handPost,  p, post), remove the assertion for calling smithyCard() as it is a void function.
2.	Compiled with:  gcc -o cardtest2 -g cardtest2.c  dominion.c rngs.c
3.	Bugs found: gain four cards instead of three.
Test feast card:
1.	Changes in my testing method: Function name and parameters uses  to call feastCard  was changed to feastCard(supplyPos, handPos, p, post), and remove the assertion for calling feastCard() as it is a void function.
2.	Compiled with: gcc -o cardtest3 -g cardtest3.c  dominion.c rngs.c
3.	Bugs found: no discardCard() to dump the card just played.
Random test adventurer card:
1.	Changes in my testing method:  Function name and parameters used to call the adventure card was changed to adventurerCard(p, post), remove the assertion for calling adventureCard() as it is a void function.
2.	Compiled with:  gcc -o randomtestadventurer -g randomtestadventurer.c  dominion.c rngs.c
3.	Bugs found: same as before.
Random test smithy card:
1.	Changes in my testing method: Function name and parameters uses to call smithy card was changed to smithyCard(handPos, p, post), remove the assertion for calling smithyCard() as it is a void function.
2.	Compiled with:  gcc -o randomtestcard -g randomtestcard.c  dominion.c rngs.c
3.	Bugs found: Same as above.
Test results for cutpurseCard(), getCost(), isGameOver(), scoreFor(), gainCard() are the same as the teammate #1.
