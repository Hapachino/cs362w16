/*  Paul Zotz
    CS 362 Winter 2016
    Assignment 5 - Bug Fixes

    EXISTING DOMINION BUGS:
    cardEffect(): - case baron:
        Bug7: card not put onto played pile
        Bug8: Extra Card in hand after card played

        Both of these bugs are due to discardCard() not being called before the end of the code for baron. Fixing both was just a matter of
        adding a call to discardCard at line 835 with the flag set to add baron to the played pile.

    adventurerCard():
        Bug4: Adventurer card not put on played pile
        Bug5: Extra Card in hand after card played

        Similar to the above set of bugs. Fixed by adding call to discardCard at line 1299.

        In both cases, this was a pretty obvious error with the dominion code received that, in the case of adventurer, my test suite really
        should have caught. To be honest, I wasn't really looking too hard for bugs that I did not introduce but, as my teammate's tests show,
        they were definitely there. Frustratingly, I noticed that adventurer wasn't discarding, that other cards tested were, and that I
        had to modify my tests accordingly to check card counts after playing that card. This should have been a red flag but instead I just
        assumed that it was expected behavior without giving too much thought to the actual game mechanics involved.

        I consider this a lesson learned in not making assumptions about the correctness of code to be tested!

    INTRODUCED BUGS:
    playAdventurer():
        Fixed bug that caused player to draw 3 treasures instead of two - modified line 1278 to change <= to <.
    playSmithy():
        Fixed bug that caused smithy to draw 1 less card than expected - initialized index value of for loop at line 1261 to 0 instead of 1.
*/
