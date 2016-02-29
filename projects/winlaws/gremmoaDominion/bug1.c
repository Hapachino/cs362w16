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
 * Bug #3 Encoutered: Other players did not receive an extra card during
 * playCouncilRoom do the loop not resetting after going executing logic for
 * giving current player 4 cards
 * Error Messages
 * --- Other Player ---
 * hand count = 0, expected = 1
 * Assertion failed: (testG.handCount[otherPlayer] == G.handCount[otherPlayer] + otherPlayerNewCards), function main, file cardtest4.c, line 57.