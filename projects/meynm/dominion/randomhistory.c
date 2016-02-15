/*
 * randomhistory.c
 * Matthew Meyn
 * 2016/2/7
 *
 * Development of randomtestadventurer.c
 *
 * When measuring dominion.c coverage with my first version of randomtestadventurer, gcov reported
 * statement coverage of 18.50%.
 *
 * Randomizing the cards/count in the player's starting hand increased statement coverage to
 * 22.74%. This was probably mainly because as part of my code to prepare the test, I used
 * endTurn() to set up the player whose turn was to take place. Therefore, that function got
 * covered even though it was not really a target of my test. I then randomized the starting card
 * count in the player's deck as well as the cards in that deck. To try to get a variety of
 * combinations of hand sizes and deck sizes, I varied the range of the counts by test count. The
 * range for deck count rotates on a four-test cycle. The range for hand count rotates on a three-
 * test cycle so that various ranges for hand and deck count are matched against each other.
 *
 * When I randomized the player's starting deck, coverage increased to 26%. This appears to be due
 * primarily to the function drawCard(), which had been covered much less in previous tests but was
 * now covered more now because I had assigned many larger decks with fewer treasure cards, which
 * meant that more cards had to be drawn to find the two treasure cards required by the Adventurer
 * card. In particular, the lines from about 615-650 had not been covered in the old test but were
 * covered in the new test. These lines are the branch that executes when the player's deck is
 * empty and a card is drawn. Apparently, this never happened in the old test, because the test
 * player's deck was always a new deck with plenty of treasure cards in it.
 *
 * This updated test also uncovered new faults. Mostly when the deck count is small (less than 10),
 * the test fails. I suspect I have found the reason: in playAdventurer(), if the player has no
 * cards left in the deck, shuffle() is first called, which is not very useful, because shuffle()
 * checks the same condition and returns -1 if the deck is empty. So, drawCard() is then called
 * with an empty deck, and drawCard() attempts to repopulate the deck:
 *
			  for (i = 0; i < state->discardCount[player]; i++)
					{
						state->deck[player][i] = state->discard[player][i];
						state->discard[player][i] = -1;
					}
 *
 * But of course if state->discardCount[player] is 0, this has no effect. Eventually, it is
 * discovered that there are still no cards in the deck, and drawCard() returns -1. The real
 * problem is that the calling function makes no check to see whether drawCard() was successful. It
 * simply assumes that whatever card is the last card in the player's hand is a newly drawn card
 * and procedes from there. Thus, playAdventurer() thinks it is drawing cards when it really isn't,
 * and the player does not end up getting the proper number of cards. The player does not end up
 * with +2 treasure cards, and the test fails.
 *
 * Another bug was found when testing the boundary case of when the player already has the maximum
 * hand. There should be a check in the software for when this happens, because without it, cards
 * can continue to be drawn and their values are written past the bounds of hand[currentPlayer],
 * which obviously can corrupt the game state or crash the program with a memory error.
 *
 * It should be noted that the game's instability near boundary values for handCount and deckCount
 * forced me, for the final version of the test, to limit the ranges of values tested somewhat. I
 * required the deck count to be between 10 and 100 less than the MAX_DECK. I also required hand
 * count to be between 5 and the deck count.
 *
 * Over all, this test ended up covering 26.4% of statements and 21.25% of branches in dominion.c,
 * with 19.89% of branches being taken at least once.
 *
 * ------------------------------------------------------------------------------------------------
 *
 * Development of randomtestcard.c, testing the Steward card
 *
 * The initial version of randomtestcard.c produced dominion.c statement coverage of 25.82%. This
 * version played the Steward card with a game state initialized with a random number of players,
 * a random player, the card in a random hand position, and a random choice of which of the 3
 * actions to take (draw two cards, get two coins or lose two cards). In case the third option was
 * chosen, the cards to get rid of were selected to be the last two in the player's hand.
 *
 * When I randomized the choice of cards to get rid of, coverage only increased  to 28.7%, but even
 * through this increase in coverage was relatively modest, a new fault was exposed: when the hand
 * position of the Steward card was last or next to last, the test case failed because the player
 * in the post-state did not have the correct number of cards. The player should have one fewer of
 * each card put in the trash, but in fact had two fewer of one of those cards. The reason appears
 * to be a bug in the code implementing the card in refactor.c, line 180:
 *
  	  	  	  discardCard( handPos, currentPlayer, state, 0 );
 *
 * The problem is handPos, which is passed as a parameter to the card function. This is the
 * position of the Steward card, that is, the position when the function is called! But during the
 * function's normal operation, we get the lines
 *
 	 	 	 discardCard( choice2, currentPlayer, state, 1 );
 	 	 	 discardCard( choice3, currentPlayer, state, 1 );
 *
 * which result in the cards in the player's hand being moved around. So the Steward card can
 * easily end up in another position. And it will end up in another position if it is the last or
 * next to last card in the hand. So the Steward card may remain in the hand and another card put
 * away instead. Thus, the counts are incorrect.
 *
 * It should be noted that all tests in randomtestcard will fail unless a bug is first fixed in the
 * function discardCard(), which never puts cards in discard[player], so every card that goes to
 * that function is lost as the function is written. This is because randomtestcard checks to see
 * that the player has either (effect choices 1 or 2) the same number of cards when all piles are
 * counted, or (effect choice 3) two fewer cards total.
 *
 * Over all, the final version of randomtestcard produced statement coverage in dominion.c of
 * 28.46% and branch coverage of 22.89%, with 20.44% of branches taken at least once.
 */
