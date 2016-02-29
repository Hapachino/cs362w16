Megan Fanning
//NOTE: I removed Jennifers test cases (unittest* and cardtest* and random*) from my copy of her copy 
//(MendozaDominion) This is so that none of my tests were accidentally confused for hers when I copied my test cases into my copy of her directory.


Bug:
unittest 1: playcard
Error: all of the tests failed due to a bad exit status from the play card function.

unitTest 2: game is over
Error: 991 of 2000 tests had a negative supply count indicating either a bad game state/intialization

unitTest 3: full deck
did not catch any errors

unitTest 4: endturn
Error: I had to alter my unit test4 so that the assert on memcopy size mismatch threw an error instead of exitted using assert. Once the assert was removed a segfault occured.
This test had to be commented out of the makefile to allow the other tests to run.

cardtest1: adventurerCard
had to alter name of the function and accept the returned int
new code
    int success
    success=playAdventurer(struct gameState *state);
    if(success!=0){
        #if (NOISY_TEST == 1)
        printf("error inside play test adventurer");
        #endif
        return 1;
    }
error:segfault

Card Test 2: Salvager
 The rules state If you have at least one card in your hand, then you must trash one.If you don't have a card in hand left to trash, you get no Coin, but still get the +1 Buy. The design of this card doesn't account for if a user chooses a card which isn't in their deck.
error: Segmentation fault (core dumped)
likely caused by whoseTurn accessing a bad game state or by discardCard, it segfaults before reporting any error even with several runs indicating that it's not the randomization aspect producing this segfault.

Card Test3: Smithy
altered function prototype to match teammates function
error: segfault

Card Test 4:village
altered function prototype to match teammates function
error: segfault
