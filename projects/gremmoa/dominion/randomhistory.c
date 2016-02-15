/*
 * My random tester of playAdventurer upped my branch coverage in playAdventurer
 * to 100%.  It now takes all possible branches thanks to randomizing hand size
 * and contents and deck size and contents.
 *
 * Thanks to random testing I finally caught the bug I introduced in
 * playAdventurer. Because I randomized the deck size and the discard deck
 * contents, I was finally encountering treasure cards other than copper.  The
 * default deck the game initiates with contains 4 copper, so with my unit tests
 * I was never getting the opportunity to run into the bug where I have a silver
 * or gold treasure card.  The bug prevents silver or gold treasure cards from
 * being counted as treasure.  In my discard deck I made sure to put 3 random
 * treasure cards into it, ensuring that at the very least, over the course of
 * 1000 tests, a silver or gold would end up in hand.
 *
 *
 * My random tester of playSmithy doesn't up branch coverage, as it was already
 * at 100%, but it is still useful as it tries playSmithy with a large number of
 * different possible hand sizes and hand setups.
 *
 * I output all of the random variables being inserted into the functions so
 * that I can see what the input is and what the output is.  Even though this is
 * randomized, if I know what the input is, I should know what the output is for
 * any given input.
 */