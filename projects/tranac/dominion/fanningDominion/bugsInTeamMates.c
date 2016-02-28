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

Card Test 2: Feast
this code hadn't been refactored by my partner so I have skipped this test

Card Test3: Smithy
altered function prototype to match teammates function
error: segfault

Card Test 4:village
altered function prototype to match teammates function
error: segfault
