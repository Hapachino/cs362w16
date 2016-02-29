/*************************
 * Eric Olson
 * CS362_400 Assignment 3
 * Discussion of Coverage Attained
 *************************/

After running all 8 tests GCOV was used to determine coverage of dominion.c.  The total statement
coverage of 29.91% and branch coverage at 24.82%.  Generally these would be very unimpressive numbers
and indicitive of an underpreforming test set.  They however consider the entirity of dominion.c, and
I only focused on the 8 functions under test.  I have broken out function coverage below.  In addition
to coverage I would argue many strengths of the test suite, I generally cover edge cases (no cards,
max cards, shuffles required etc), as well as used at least some random testing on 5 of the 8 test cases.
In addition I attempt to evaluate every possilbe gameState value giving me a high comfort level that
no inadvertant changes have occured.  Some weaknesses of my current approach is that I only test the
function in question, so do not have good interfunction interaction visibility, and I only tested with 2
players.

/////cardtest1.c - smithy_play()/////
100% of statements covered.
100% of branches covered.
Small number of calls however, only 2 calls to the function in fact.  This could be improved with random
testing or additional interesting scenarios identified.  All conditionals covered.

/////cardtest2.c - adventurer_play()/////
100% of statements covered.
100% of branches covered.
All conditionals were covered except 1, and this is due to a bug.  The remaining conditional would be
for the final '== gold' to be evaluated true, but since it currently is a repeated '== silver'
it will never return true because if true the if statement would short circuit as true with the first
'== silver' check.  Again a small number of calls made here, more random testing or additional scenarios
could be beneficial.

/////cardtest3.c - council_room_play()/////
100% of statements covered.
100% of branches covered.
All conditionals covered, but again only 2 calls to this function were executed.  This test in particular
could benefit from additional players since this function actively draws a card for all other players.

/////cardtest4.c - village_play()/////
100% of statements covered.
No branch/conditionals in function.
This function is very basic, but was only executed under 2 scenarios.  Again additional tests, or
random testing might improve confidence.

/////unittest1.c - updateCoins()/////
100% of statements covered.
100% of branches & conditions covered.
Random testing including edge cases (no coins/no bonus) ensured this funciton was
fairly throughly tested.

/////unittest2.c - gainCard()/////
100% of statements covered.
100% of branches & conditions covered.
Random testing included edge cases: attempt for card no longer available & not in current
game.  Also tested all 3 card destinations, hand, deck, discard.

////unittest3.c - shuffle()/////
100% of statements covered.
100% of branches & conditions covered.
Random testing included edge cases: No cards in deck to shuffle, and all random combinations of 
cards elsewise.  Checked cards were retained in hand, as well as actually changed locations.

/////unittest4.c - discardCard()/////
88% of statements covered.
1 uncovered branch.
The only uncovered content is the scenario when only 1 card is left in hand.  However this is an 
if/else case along with 'last card in hand played'.  When only 1 card is left and it's also the last 
card in hand, and therefore both secnarios are true.  Only one is executed (the first) and the else is never
called (and could really be removed altogether from the code).  Otherwise random testing included edge 
cases: 1 card in hand, last card in hand played.
