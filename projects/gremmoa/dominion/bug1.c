/*
 *
 * Bug #1 Encountered: Smithy returns too many cards.
 * Error Messages
 * --- Current Player ---hand count = 8, expected = 7
 * Assertion failed: (testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded)
 *
 * Bug #2 Encountered: A bug I did not introduce, playAdventurer never discards
 * the played card, so the player always ends up with too many cards in hand.
 * Error Messages
 * --- Current Player ---
 * hand count = 7, expected = 6
 * Assertion failed: (testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded)
 *
