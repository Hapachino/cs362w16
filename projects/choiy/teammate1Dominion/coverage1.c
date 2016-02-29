Jennifer Frase
CS 362 A3

The dominion.c code coverage says that I only covered about 41.77% of the code. Considering
that I was focusing only on 4 functions and 4 cards, this is not very suprising to me.

getCost: unittest1 shows that I covered only about 77% of the lines. Based on the #'s this is because
the tests have never failed and so never go into the fail branches of my tests.
The dominion.c shows that I covered 100% of the lines. I also looked at each case the same
number of times, except the last one which I look at twice. Considering the test I ran
this is the expected result.

updateCoins: unittest2 shows 90% of the code being covered which is once again because
none of the tests failed so the fail routes were never accessed.
Dominion.c Shows that I covered 100% of the lines. with only some of the lines happening
4% of the time. Based on my test and the code, this is also expected because the cards
in the hand are only copper, silver, and gold 1/26 times which is about 4%.


scoreFor: unittest3 says 95% of the code is covered, which in this case is becuase
some of my fail routes were never accessed, while the high % is becuase some where,
which also resulted in my success statement never executing.
The dominion.c results, shows I covered 100% of the lines.

isGameOver: unittest4 gives a coverage % of about 74, which is for the same reason as
the other functions, parts of my test never failed so never executed, while others
always failed, never allowing for the success statement to execute.
Dominion.c shows I covered 100% of the lines

smithy: cardtest1.c has a coverage of about 74% for the same exact reason as all the rest:
failure to ever deviate from a result.
Every line of smithy in dominion.c is hit at least 4 times, which is a result of 4 players.

adventurer: cardtest2.c has only 66% coverage, but considering the number of test ran
in that card test, that is not suprising. This is especially the case, because I put in
some for loops which never get used becuase the initial value is already outside the
conditional statement. Those were mainly there are insurance, but since they really are
not needed, I could instead test for the opposite becuase if it ever was to enter
the for loop, that would be a sign something was wrong.
Shows that there were no missed lines in dominion.c's code for the adventurer card.

gardens: cardtest3 gives a good 85% as only my fail route is never executed. This makes
sense, since gardens doesn't change anything the gamestate, since it is a victory card
it can never be played, just counted at the end. So one test to make sure the function
returns correctly and another to make sure the gamestate doesn't change is all that is
needed.
Dominion.c show I visit the one line 4 times, once for each player.

sea hag: cardtest4 is one of my longer tests and so unsuprisingly has the low coverage
of 60%. This is once again due to some routes never changing.
The dominion.c results to say that I visit every line in sea hag's code. This is once
again expected purely based on dominion.c's code, since it is impossible not to visit
every line of it once it is invoked.
