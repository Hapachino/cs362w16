My coverage statistics for these 8 tests are as follows:
  Lines executed:22.58% of 713
  Branches executed:22.57% of 443
  Taken at least once:15.58% of 443

  Some factors that might be misleading in these statistics are the fact that because I
introduced bugs into several of the card functions, I decided to make 'clean' and 'dirty'
versions of card functions so fo example the smithy card function ( which was put into a
separate function from the previous assignment  ) had bugs, which would cause my tests
to fail. In order to verify they were working on the 'clean' functions (i.e. without
bugs I introduced myself) I created separate 'clean' functions and tested those. The
result is that I can verify the tests pass for the clean versions and fail for the
versions where I introduced subtle bugs. While this is a great sign the tests are
in fact testing relevant outputs, it created several more lines of code in the dominion.c file
which means that my lines executed as a percentage went down ( because I am testing the clean
versions only). So in effect there are more lines of code in my dominion.c than in the original
file so my line executions as a percentage should be slightly lower than if I only had one
version of each card function. This was not the case with other methods like updateCoins where
no bugs were introduced.
  For both the cards and the functions I did test, I have 100% branch coverage within those functions.
I did this by first making sure the functions were being called correctly in the test and then
manipulated input values until all branch paths were taken and made relevant assertions about them.
This means that for reasonable inputs, the functions are working correctly. One area I did not test
thoroughly was in unreasonable inputs to functions, or extreme values. For example what happens if I
call the function with more cards in the player's hand than there are cards in the deck? In fact, for
many of the functions, they would still produce the correct results, but nonetheless it is worth mentioning
for the sake of improving my test suite in the future. 
