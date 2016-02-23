/*
                                        randomhistory.c
 Patrick Burrell
 CS 362 - Winter 2016 
 Assignment 4
 
 randomtestadventurer.c - Adventurer card
    I was able to reuse much of the test suite I developed for Assignment 3 for 
 testing changes in the game state. Most of the coding work revolved around
 deciding what to randomize and how to properly randomize these parameters. I 
 aimed to randomize everything that logically made sense in terms of having a role
 in the execution of playing the adventurer card. These randomized parameters 
 included the number of players in the game, the current player, the cards in the 
 player's hand and deck, the number of coin cards in the player's hand, and which
 coin cards these were.
    The most difficult part about writing the test was keeping track of the 
 "weird" cases that required a shuffle of the deck to get to two treasure 
 cards in a player's hand. If a player has 1 or 0 treasure cards in their deck, 
 then their discard pile will have to be shuffled back into the deck until two 
 treasure cards are pulled. Figuring out how to ensure the player still made it to
 two treasure cards in this scenario while also keepign track of the value of those
 cards and how many cards needed to be discarded in the process was fairly time 
 intensive. I did manage to track the value of the treasure cards pulled for the 
 purposes of testing the change in coins for the game state, but the number of 
 cards discarded is not actually tested in these two scenarios becuase I did not 
 find a feasible way to do this with the randomization inherent in the shuffle() 
 funciton. This parameter's lack of testing in these two cases is somewhat mitigated
 by testing that a player's hand always increases by two cards and that the total 
 number of cards remains constant.
    Many of the randomly generated game states resulted in a failure in the call
 to the playcard() function. There are a limited number of conditions that cause a 
 failure for this function, so I was able to track it down with some trace statements. 
 It turns out that the failure is actually a result of the shuffle() function returning
 -1 when the player's deck count is 0, which I believe is a bug in the implementation. A
 deck of size 0 would mean that all of the player's discarded cards need to be shuffled 
 back into the deck; it should not result in the call to shuffle() failing.
    BUGS: 
    There were two bugs related to discarding that came up in the random test that
 were also discovered from the Assignment 3 unit tests for Adventurer. An additional
 test I added for this randomized version was a check that the total number of cards
 in a player's hand, deck, and discard pile remains the same before and after the card
 is played. This test failed intermittently, and it also appears to be due to the bug
 I introduced in Adventurer because it is related to discarding as well: the total 
 card number changes when the discard count and deck count changes don't properly 
 balance each other. s
    COVERAGE:
    Assignment 3: playAdventurer called 5, returned 100%, executed 86%
    Assignment 4: playAdventurer called 382, returned 100%, executed 93%
    The increase in blocks executed was due to an additional branch being covered in 
    the random test instance. This branch happens to be a cause of some bugs in the 
    program, so it was an important branch to have hit, meaning that the random test
    addition was an improvement for this case.
 
 randomtestcard.c
    This test program was also very similar to the one I wrote in Assignment 3 for 
 the Great Hall card. The items I again tried to randomize every element of the game
 state that made logical sense, but there were fewer options in this case as compared 
 to adventurer since there is no draw, discard, or coin component to playing this
 card.
    BUGS:
    This randomized test suite caught the same issue with Great Hall that my prior 
 version did: the player's discard count does not increase after playing the card. 
 This problem is not unique to playing Great Hall but rather seems to be a bug in the 
 overall implementation of the game. 
    An additional issue that came up was the failure rate of playCard() with the 
 randomized conditions. The test runs for 1,000 trials at a time, and this function 
 fails (returns -1) over 60% of the time consistently. The playCard() function returns
 -1 when the phase != 0, actions < 1, cardEffect fails, or (in the case of great_hall), 
 drawCard() or discardCard() fails. Actions and the phase are set before the call to the 
 function, and trace statements showed that they're values are okay. The discardCard() 
 function never returns -1, and the great_hall case in the switch statement doesn't either, 
 so that leaves drawCard() as the remaining possibility. Within that funciton, the only
 possibility I could find was in the call to shuffle(), which fails when the deckCount 
 is 0. This possibility doesn't make sense as the initializeGame() function ensures that
 every player has a positive deck count at the onset of the game. This issue will 
 require further investigation. 
    COVERAGE:
    Assignment 3: Every line for great_hall case ran an equal number of times
        shuffle() call 118, returned 100%, executed 100%
        drawCard() called 271, returned 100%, executed 75%
        discardCard() called 48, returned 100%, executed 100%
    Assignment 4: Every line for great_hall case ran an equal number of times
        shuffle() called 2971, returned 100%, executed 93%
        drawCard() called 5351, returned 100%, executed 41%
        discardCard() called 351, returned 100%, executed 80%
    The comparisons don't exactly work for great_hall becuase the numbers for Assignment
    3 are cumulative for all 8 unit tests written. I included shuffle, drawCard, and 
    discardCard because they were the functions used in conjunction with playing the 
    great_hall card. Writing a test suite for any or all of those functions would be the
    next step in tracking down the root cause of the bug discovered in great_hall from 
    the random testing.
 
 */
