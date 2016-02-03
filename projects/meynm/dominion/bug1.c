/*
 * bug1.c
 * Matthew Meyn
 * 2016/2/2
 *
 * Documentation of bugs found in card tests/unit tests
 *
 * -----------------------------------------------------------------------------------------------
 *
 * void playSmithy( int currentPlayer, struct gameState *state, int handPos )
 * tested in cardtest1
 *
 * None of the tests are passed. Using the Eclipse debugger, I find that this happens because the
 * value of currentPlayer that is passed to discardCard() is incorrect. Looking more closely, I
 * should have remembered that introduced this bug: I put the arguments to that function in the
 * wrong order. (I switched currentPlayer with handPos.) There is another bug I had introduced,
 * which was changing the trashFlag argument from 0 to 1. This would be a more subtle bug, because
 * it would result in the card being removed from the game rather than kept in the player's pile.
 * 
 * However, even when I fix all the bugs I introduced, none of the tests are passed. After some
 * investigation, I find that this is because we still end up with the player possessing fewer 
 * cards after playing the Smithy than before playing it. This happens even with the original code,
 * I think, because of what appears to be a preexisting bug in discardCard(). Even if trashFlag is
 * not set, the played card is inserted in the array playedCards before it is removed from the 
 * player's hand. But, as far as I can tell, there is no code that ever moves the card from 
 * playedCards back into the player's deck, so it really makes little difference whether trashFlag
 * is set or not: the card is still lost from the pile of cards possessed by the player. Therefore,
 * we end up with the wrong number of cards at the end of the transaction. This violates an 
 * invariant of the Smithy card, which is that there should be no change in the set that is the 
 * union of hand, deck and discard piles.
 *
 * -----------------------------------------------------------------------------------------------
 *
 * void playAdventurer( int currentPlayer, struct gameState *state )
 * tested in cardtest2
 *
 * As refactored with the newly introduced bugs, playAdventurer causes a segmentation fault. This
 * happens because the variable int z is not initialized. Therefore, the line
 *
 * 		state->discard[currentPlayer][state->discardCount[currentPlayer]++] = temphand[z - 1];
 * 
 * causes obvious problems when z is a random number. When this superficial bug is fixed, another
 * initialization problem becomes evident: drawnTreasure also needs to be initialized to 0. When
 * this does not happen, drawnTreasure is likely to be greater than 2, which means that the while
 * loop body that draws cards until 2 treasure cards are drawn never executes. Thus, the test 
 * almost always fails with drawnTreasure uninitialized.
 *
 * Another bug was found that causes major problems: 
 *
 * 		state->handCount[currentPlayer--] 
 *
 * should be 
 *
 * 		state->handCount[currentPlayer]--
 *
 * When currentPlayer is 0 (that is, the first player), currentPlayer becomes -1, which obviously
 * is not a valid value. That invalid value gets passed around, causing numerous bad writes to 
 * memory because the player value is usually used as an array index. Thus, at best the game state
 * becomes corrupted, and sooner or later, a seg fault happens.
 *
 * The last bug concerns z, the variable that keeps track of how many cards are in the temporary 
 * hand that holds the non-treasure cards that have been drawn. The problem is that every time a 
 * non-treasure card is drawn, z should be incremented, but it is not. Therefore, every card that
 * gets drawn that is not a treasure card gets lost. The program thinks there are no cards in the
 * temporary hand, so it does not put the cards in the temporary hand back into the pile.
 *
 * -----------------------------------------------------------------------------------------------
 *
 * int playMine( int currentPlayer, struct gameState *state, int handPos, int choice1, int choice2 )
 * tested in cardtest3
 *
 * With the bugs that were introduced, playMine() passes none of my test cases. This is the result
 * of several bugs, some of which I introduced, one of which seems to be preexisting. The one that
 * seems to have been there already is a > sign that should be <, specifically lines 73-76 of
 * refactor.c:

	   if (( getCost( state->hand[currentPlayer][choice1] ) + 3 ) > getCost( choice2 ))
		{
			return -1;
		}

 * These lines should be validating that the player's choice of card to gain does not cost more
 * than 3 plus the cost of the card being thrown in the trash. What it actually does is validate
 * that the chosen card does not cost more than 3 coins less. This bug accounts for 1 of the 5
 * failures, because it causes the program to accept a request to trade copper for gold, which
 * should not be permitted, but is permitted because gold does not cost less than copper.
 *
 * Another bug is that the validation code from dominion.c checks only that the requested card be
 * from the range of valid enum values for card. (67) This is not consistent with the card's rules,
 * which allow a treasure card to be traded only for another treasure card. Thus, when the player
 * requests to gain a treasure map card, the request is allowed even though it shouldn't be. Since
 * this line is checking only that the value of choice2 is between 0 and 27, it does not seem to
 * make much difference that I introduced a bug by substituting choice1 for choice2. choice1 is the
 * index of the card in the hand that the player wants to trade in, so it will probably always be
 * between 0 and 27 anyway.
 *
 * I had more "success" causing problems with another bug I had introduced: in line 78,
 *
   	   gainCard( choice2, state, j, currentPlayer ); // j should be 2

 * I substituted j for 2 in the original code. This causes problems because the 3rd argument to
 * gainCard is a flag specifying where to add the new card. The proper value, 2, indicates the card
 * is to be added to the player's hand. As it happens, j is the enum value of the card the player
 * is getting rid of. So, unless the player happens to be getting rid of an Estate card (not
 * implausible but not certain either), the newly gained card will go to the wrong place, which
 * will not satisfy the postconditions I am checking for in my tests.
 *
 * -----------------------------------------------------------------------------------------------
 *
 * void playSteward(int currentPlayer, struct gameState *state, int handPos, int choice1, int choice2, int choice3)
 * tested in cardtest4
 *
 * I had introduced a single bug in this function, which still managed to create 490 failures out
 * of  1003 tests. It seems as though the reason it didn't cause more tests to fail is that the bug
 * is only in the section of the function that executes when the player has chosen to throw 2 cards
 * in the trash. Specifically, the bug is on line 174,
 *
 	 	 discardCard( choice1, currentPlayer, state, 1 );
 *
 * where choice1 should be choice2. This is important because choice1 is actually a flag indicating
 * which of the available actions the player has chosen. This code executes when choice1 is neither
 * 1 nor 2. (Is it supposed to be 0 or 3, I wonder? Either will work.) In any case, the first
 * argument here is supposed to be the hand index of the card to be thrown out. So, obviously,
 * unless the player happened to want to throw out the card at position 0 or 3 or whatever was
 * passed in as the choice1 flag value, the wrong card will end up in the trash.
 *
 * -----------------------------------------------------------------------------------------------
 *
 * Unit Tests
 *
 * My unit tests tested buyCard, shuffle, gainCard and fullDeckCount. No bugs were discovered in
 * these functions.
 */
