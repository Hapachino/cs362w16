For the purposes of this document, only coverages of the pertinent tested sections of dominion.c will\
be referred to. Using the output of the .gcov file, you can see that the following coverage information\
is accurate. The sections of code are listed in the order that they appear in the dominion.c.gcov file.\
\
isGameOver(): I used a branch coverage approach to this function in order to cover every condition in the two if\
statements. That is, the condition that the province supply be both 0 and non zero, and also the condition that the count of empty kingdom card supplies be 3 and not 3. I also tested an empty kingdom card supply count of 2, 1, and 0, giving the expected results. Every line of this function has been covered.\
\
refactoredSmithy(): This was a relatively easy function to cover as any input gains full coverage. I took a boundary coverage\
approach in order to test the error condition when an invalid hand position is entered as a parameter. This test turned out to be\
fruitful, as there is no error handling for improper input.\
\
refactoredVillage(): Again, full coverage is gained in this by any input. A statement approach could be said to be used, since it is\
given that each statement is executed.\
\
refactoredAdventurer(): A branch approach was attempted here, but failed to reach full coverage. I failed to create a condition in\
which the deck would go empty, needing a re-shuffle. This oversight means that a line of code in refactoredAdventurer is not\
ran. Aside from this condition, all other conditions and lines in the function were covered.\
\
council_room (in cardEffect): Statement coverage, all statements executed with any input. Full coverage.\
\
discardCard(): An error in my testing was revealed here in the fact that a branch of code that I attempted to test, did not in fact get \
tested. The condition that there is only one card remaining and that card gets discarded, I thought I had addressed on test 2 of \
unittest3.c. However, the gcov data reveals that this is not the case. All other branches/ statements were covered.\
\
gainCard(): The if statement in this function is critical, therefore a branch approach was implemented. Every branch and statement\
was covered.\
\
updateCoins(): Similar to gainCard, the function is relatively simple and heavily relies on an if statement. Therefore all three\
conditions were reached by branch coverage. All lines covered.}
