/**
 * Class: CS362 Winter 2016
 * Student:  Jeannine Amm
 * Assignment 5
 *
 *********************************************
 * Bug Report for Teammate1 - Janel Buckingham
 **********************************************
 * unittest1.c - int getCost(int card)
 * 	ALL tests passed
 *
 * 	Bug1: Calculated points in getWinners does not equal expected points.  With incorrect point
 * 		values the winner cannot be calculated correctly.
 *
 * 	Sample output:
			TEST: 1, FAIL: Player: 0 of 3 players
			Score: 71, Expected: 119, Winner Val Returned: 1, Expected: 0
			HAND: 3,9,13,23,25,16,0,11,24,
			DECK: 16,7,26,9,11,7,4,25,23,16,19,11,18,8,20,17,19,8,7,15,22,18,18,4,4,15,3,20,16,15,18,5,23,17,15,7,24,19,6,21,8,25,6,0,6,0,17,25,8,25,14,3,16,6,7,20,21,11,14,11,26,5,16,22,23,4,3,21,24,9,16,5,8,22,5,14,22,23,13,4,22,1,7,11,7,15,5,2,26,20,13,25,26,2,21,23,7,24,17,4,7,7,10,15,2,
			DISCARD: 16,3,25,12,17,2,7,18,10,19,26,25,25,1,25,18,15,24,18,18,18,14,26,16,4,3,24,11,14,12,14,3,16,13,16,6,16,24,25,0,17,25,26,15,26,24,7,15,21,25,6,13,12,5,3,17,9,0,2,23,13,17,0,2,3,17,9,20,14,8,20,5,6,19,20,6,17,1,21,
			CURSE: 6, ESTATES: 3, DUCHY: 6, PROVINCE: 9, GREAT_HALL:12, GARDENS: 2, totalCards: 193

			TEST: 1, FAIL: Player: 1 of 3 players
			Score: 5, Expected: 208, Winner Val Returned: 0, Expected: 1
			HAND: 25,11,6,1,2,
			DECK: 16,1,4,12,15,21,13,17,25,3,0,19,18,8,13,23,15,5,17,21,23,18,16,7,17,17,6,2,23,8,4,12,10,9,25,25,3,12,16,2,15,16,21,7,25,7,3,14,13,20,8,9,11,25,17,2,15,23,4,12,4,9,25,15,18,23,13,22,9,2,24,25,19,19,5,18,0,8,5,13,2,14,23,14,12,13,16,0,10,21,13,15,3,11,3,22,8,17,17,17,19,15,15,12,8,20,3,8,2,9,22,5,23,18,19,9,5,8,10,15,3,23,4,6,7,8,2,15,25,19,6,18,8,21,3,16,15,7,25,18,16,20,23,13,11,16,22,17,24,5,6,1,2,10,8,9,19,10,25,17,2,5,8,11,0,11,0,15,18,25,7,8,19,3,21,3,19,16,21,17,22,0,18,24,11,26,7,3,9,6,20,12,11,2,23,11,
			DISCARD: 13,24,0,5,23,7,13,15,
			CURSE: 7, ESTATES: 3, DUCHY: 11, PROVINCE: 11, GREAT_HALL:9, GARDENS: 5, totalCards: 209

			TEST: 1, FAIL: Player: 2 of 3 players
			Score: -25, Expected: 165, Winner Val Returned: 0, Expected: 0
			HAND: 4,24,13,21,20,
			DECK: 14,13,18,25,13,25,1,23,5,22,9,17,24,6,2,11,4,2,16,0,10,3,15,22,11,8,26,8,22,21,2,9,8,20,7,22,19,9,18,24,4,1,15,1,7,17,12,12,20,2,12,4,5,1,26,16,9,26,25,
			DISCARD: 5,20,0,14,2,20,22,24,13,4,16,10,8,17,26,9,25,16,22,10,9,24,23,13,2,24,13,19,7,12,17,12,5,17,0,8,11,22,5,24,26,21,8,7,12,7,17,11,24,13,21,7,11,18,21,14,15,7,6,23,19,23,9,25,14,9,6,26,4,12,24,4,6,6,11,19,14,2,3,11,16,24,19,0,15,13,14,4,20,20,0,13,17,10,11,5,19,18,4,24,3,2,1,10,8,13,2,23,15,5,7,5,3,0,5,19,13,19,24,6,13,25,20,3,8,5,8,0,23,13,24,0,16,26,11,24,12,13,20,0,19,1,6,22,1,
			CURSE: 9, ESTATES: 7, DUCHY: 9, PROVINCE: 5, GREAT_HALL:6, GARDENS: 5, totalCards: 209

			TEST: 1, PASS: Player: 3 of 3 players
			Score: 0, Expected: 0, Winner Val Returned: 0, Expected: 0
 *
 * int playSmithy(int handPos, struct gameState *state);
 * 	Bug2: Smithy Card not put onto played pile
 * 	Bug3: Extra Card in hand after card played
 * 	Bug4: Extra Card missing from deck after card played
 *
 *	Sample Output:
			TEST FOR SMITHY FIRST CARD PLAYED
			FAIL:  Post HandCount Result: 10, Expected: 9
			FAIL:  Post PlayedCardCount Result: 0, Expected: 1
			FAIL:  Post Last PlayedCard Result: 0, Expected: 13
			FAIL:  Post Deck Count: 6, Expected: 7

			TEST FOR DECKCOUNT 0 DISCARDCOUNT 0 test
			FAIL:  Post PlayedCardCount Result: 0, Expected: 1
			FAIL:  Post Last PlayedCard Result: 0, Expected: 13

			TEST FOR MIXED DRAW CARDS DECKCOUNT 197 DISCARDCOUNT 73
			FAIL:  Post HandCount Result: 10, Expected: 9
			FAIL:  Post PlayedCardCount Result: 0, Expected: 1
			FAIL:  Post Last PlayedCard Result: 0, Expected: 13
			FAIL:  Post Deck Count: 193, Expected: 194

			TEST FOR ALL COINS IN DECK AND DISCARD
			FAIL:  Post HandCount Result: 7, Expected: 6
			FAIL:  Post PlayedCardCount Result: 0, Expected: 1
			FAIL:  Post Last PlayedCard Result: 0, Expected: 13
			FAIL:  Post Deck Count: 0, Expected: 1
 *
 * int playAdventurer(struct gameState *state);
 * 	Bug5: Adventurer card not put on played pile
 * 	Bug6: Extra Card in hand after card played
 * 	Bug7: Unexpected amount of cards discarded when deckCount or discardCount is greater than 0
 *
 * 	Sample Output:
			TEST FOR ADVENTURER FIRST CARD PLAYED
			Test 0: FAIL: HandCount: 9, Expected: 8
			Test 0: FAIL: playedCardCount: 0, Expected: 1
			Test 0: FAIL: playedCard: 0, Expected: 7
			Test 0: PASS: Coins discarded: Gold: 0, Silver: 0, Copper: 0
			Test 0: FAIL: DiscardCount: 1, Expected: 2, ControlHandCount: 7, PostHandCount: 9, ControlDeckCount: 10, PostDeckCount: 6, ControlDiscardCount: 0, PostDiscardCount: 1

			TEST FOR DECKCOUNT 0 DISCARDCOUNT 0 test
			Test 0: FAIL: HandCount: 4, Expected: 3
			Test 0: FAIL: playedCardCount: 0, Expected: 1
			Test 0: FAIL: playedCard: 0, Expected: 7
			Test 0: PASS: Coins discarded: Gold: 0, Silver: 0, Copper: 0

			TEST FOR MIXED DRAW CARDS DECKCOUNT 197 DISCARDCOUNT 73
			Test 0: FAIL: HandCount: 9, Expected: 8
			Test 0: FAIL: playedCardCount: 0, Expected: 1
			Test 0: FAIL: playedCard: 0, Expected: 7
			Test 0: PASS: Coins discarded: Gold: 0, Silver: 0, Copper: 0
			Test 0: FAIL: DiscardCount: 90, Expected: 91, ControlHandCount: 7, PostHandCount: 9, ControlDeckCount: 197, PostDeckCount: 177, ControlDiscardCount: 73, PostDiscardCount: 90

			TEST FOR NO COINS IN DECK OR DISCARD
			Test 0: FAIL: HandCount: 4, Expected: 3
			Test 0: FAIL: playedCardCount: 0, Expected: 1
			Test 0: FAIL: playedCard: 0, Expected: 7
			Test 0: PASS: Coins discarded: Gold: 0, Silver: 0, Copper: 0
			Test 0: FAIL: DiscardCount: 5, Expected: 6, ControlHandCount: 4, PostHandCount: 4, ControlDeckCount: 3, PostDeckCount: 0, ControlDiscardCount: 3, PostDiscardCount: 5

 *
 * Baron Card using CardEffect
 * 	Bug8: Baron Card not put onto played pile
 * 	Bug9: Extra Card in hand after card played
 * 	Bug10: Coin Bonus being not being updated
 * 	Bug11: Coins added to state->coins which is wiped before coins updated in playCard() function
 * 	Bug12: Estate supply loses more estates than expected when estate taken from supply
 *
 * Sample Output:
			TEST FOR ESTATE IN HAND, ESTATE SUPPLY > 1, CHOOSE COINS
			FAIL: Post Hand Baron Count: 1, Expected: 0
			FAIL: Last Card Played: 0, Expected: 15
			FAIL: playedCardCount: 0, Expected: 1
			FAIL: Hand Count: 6, Expected: 5
			FAIL: Coin bonus returned: 0, Expected: 4
			FAIL: Testing Values haven't changed: Coins updated to: 4, Expected: 0

			TEST FOR ESTATE IN HAND, ESTATE SUPPLY > 1, CHOOSE EXTRA ESTATE
			FAIL: Post Hand Baron Count: 1, Expected: 0
			FAIL: Last Card Played: 0, Expected: 15
			FAIL: playedCardCount: 0, Expected: 1
			FAIL: Hand Count: 4, Expected: 3
			FAIL: Estate Supply Count: 10, Expected: 11

			TEST FOR 0 ESTATE IN HAND, ESTATE SUPPLY > 1, CHOOSE COINS
			FAIL: Post Hand Baron Count: 1, Expected: 0
			FAIL: Last Card Played: 0, Expected: 15
			FAIL: playedCardCount: 0, Expected: 1
			FAIL: Hand Count: 10, Expected: 9
			FAIL: Estate Supply Count: 10, Expected: 11

			TEST FOR 0 ESTATE IN HAND, ESTATE SUPPLY > 1, CHOOSE ESTATE
			FAIL: Post Hand Baron Count: 2, Expected: 1
			FAIL: Last Card Played: 0, Expected: 15
			FAIL: playedCardCount: 0, Expected: 1
			FAIL: Hand Count: 6, Expected: 5
			FAIL: Estate Supply Count: 10, Expected: 11

			TEST FOR ESTATE CARD IN HAND, ESTATE SUPPLY = 0, CHOOSE TAKE ESTATE
			FAIL: Post Hand Baron Count: 3, Expected: 2
			FAIL: Last Card Played: 0, Expected: 15
			FAIL: playedCardCount: 0, Expected: 1
			FAIL: Hand Count: 9, Expected: 8

			TEST FOR ESTATE CARD IN HAND, ESTATE SUPPLY = 1, CHOOSE TAKE ESTATE
			FAIL: Post Hand Baron Count: 2, Expected: 1
			FAIL: Last Card Played: 0, Expected: 15
			FAIL: playedCardCount: 0, Expected: 1
			FAIL: Hand Count: 8, Expected: 7
			FAIL: Estate Supply Count: -1, Expected: 0

			TEST FOR 0 ESTATE IN HAND, ESTATE SUPPLY = 0, CHOOSE COINS
			FAIL: Post Hand Baron Count: 1, Expected: 0
			FAIL: Last Card Played: 0, Expected: 15
			FAIL: playedCardCount: 0, Expected: 1
			FAIL: Hand Count: 9, Expected: 8

 * Tribute card using CardEffect
 * 	Bug13: More actions than expected sometimes added
 * 	Bug14: Tribute Card not added to played pile
 * 	Bug15: Extra Card in hand after card played
 * 	Bug16: Next Player's cards not put onto the discard Pile after being shown
 * 	Bug17: Next Player's card are not removed from their deck after being shown
 * 	Bug18: Added coins for treasure cards revealed not added to bonus
 * 	Bug19: Added coins for treasure cards added to state->coins which is wiped before coins updated in playCard() function
 *
 * 	Sample Outputs:
			Card1: 0 - Dead, Card2: 0 - Dead (-1 indicates card not drawn)
			**Game State Checks Starting**
			TEST1 FAIL: Reported total Actions: 7, Expected total Actions: 1 (Control: 1, Bonus Actions Calculated: 0)
			TEST1 FAIL: Reported playedCardCount: 0, Expected: 1 (Control: 0, Cards Played: 1)
			TEST1 FAIL: Reported last playedCard: 0, Expected: 19
			**Next Player Checks Starting**
			TEST1 FAIL: Reported discardCount: 0, Expected: 2 (Control: 0 + Revealed Card(s): 2)
			TEST1 FAIL: Reported deckCount: 6, Expected: 8 (Control: 10 - Revealed Card(s): 2 (Expected may include Discard: 0)
			**Current Player Checks Starting**
			TEST1 FAIL: Reported handCount: 5, Expected: 4 (Control: 5 - 1 + Bonus Cards: 0)
			TEST1 FAIL: Hand index where tribute was: 19, Expected: 4 (last card from original hand)

			 Card1: 4 - Treasure, Card2: 5 - Treasure (-1 indicates card not drawn)
			**Game State Checks Starting**
			TEST8 FAIL: Reported total Actions: 5, Expected total Actions: 1 (Control: 1, Bonus Actions Calculated: 0)
			TEST8 FAIL: Reported Bonus Coins: 0, Expected: 4
			TEST8 FAIL: Reported playedCardCount: 0, Expected: 1 (Control: 0, Cards Played: 1)
			TEST8 FAIL: Reported last playedCard: 0, Expected: 19
			**Next Player Checks Starting**
			TEST8 FAIL: Reported discardCount: 0, Expected: 2 (Control: 0 + Revealed Card(s): 2)
			TEST8 FAIL: Reported deckCount: 6, Expected: 8 (Control: 10 - Revealed Card(s): 2 (Expected may include Discard: 0)
			TEST8 FAIL: Reported Last Discard: 0, Expected: 5 (Control: Second Revealed Card: 5)
			**Current Player Checks Starting**
			TEST8 FAIL: Reported handCount: 5, Expected: 4 (Control: 5 - 1 + Bonus Cards: 0)
			TEST8 FAIL: Hand index where tribute was: 19, Expected: 4 (last card from original hand)
			TEST8 FAIL: Changes not in scope:  gameState->coins changed

 * Baron Card - random check additional bugs
 * 	Bug20: Estate not added to discard pile when choice is to take an estate
 *		(Estate should be taken from supply if there are estates and added to discard)
 *
 *  Sample Output:
			Test: 0, choice: 0, hand estates: 0, handCount: 3, estate supply: 2
			Test: 0 FAIL: Post Hand Baron Count: 1, Expected: 0
			Test: 0 FAIL: Last Card Played: 0, Expected: 15
			Test: 0 FAIL: playedCardCount: 0, Expected: 1
			Test: 0 FAIL: Hand Count: 3, Expected: 2
			Test: 0 FAIL: Estate not discarded.  Last discard: 9, Expected: 1, control estate supply: 2, control estates in hand: 0, active estate supply: 0, active estates in hand: 0
			Test: 0 FAIL: Estate not added to DiscardCount.  DiscardCount: 196, Expected: 197, control estate supply: 2, control estates in hand: 0, active estate supply: 0, active estates in hand: 0
			Test: 0 FAIL: Estate Supply Count: 0, Expected: 1

			Test: 49, choice: 1, hand estates: 0, handCount: 2, estate supply: 2
			Test: 49 FAIL: Post Hand Baron Count: 1, Expected: 0
			Test: 49 FAIL: Last Card Played: 0, Expected: 15
			Test: 49 FAIL: playedCardCount: 0, Expected: 1
			Test: 49 FAIL: Hand Count: 2, Expected: 1
			Test: 49 FAIL: Estate not discarded.  Last discard: 3, Expected: 1, control estate supply: 2, control estates in hand: 0, active estate supply: 2, active estates in hand: 0
			Test: 49 FAIL: Estate not added to DiscardCount.  DiscardCount: 82, Expected: 83, control estate supply: 2, control estates in hand: 0, active estate supply: 2, active estates in hand: 0
			Test: 49 FAIL: Estate Supply Count: 2, Expected: 1
			Test 49: FAIL: gameState->coins Reported: 8, Expected: 4

 *
 * playAdventurer random check - additional bugs
 * 	Bug21: When there are less than two treasures between the deck and the discard pile - segmentation fault
 *
 * 	Note:  To get prior bug faults to report Segmentation fault was fixed and then reverted to
 * 	original upon completion.
 *
 * Sample Output:
		./randomtestadventurer >> randomtestadventurer.out
		Segmentation fault (core dumped)
		make: *** [randomtestadventurer.out] Error 139

 *
 ********************************************
 * Bug Report for Teammate2 - Paul Zotz
 ********************************************
 *
 * int getWinners(int players[MAX_PLAYERS], struct gameState *state)
 * 	Bug1: Calculated points in getWinners does not equal expected points.  With incorrect point
 * 		values the winner cannot be calculated correctly.
 *
 * 	Sample output:
			TEST: 1, FAIL: Player: 0 of 3 players
			Score: 71, Expected: 119, Winner Val Returned: 1, Expected: 0
			HAND: 3,9,13,23,25,16,0,11,24,
			DECK: 16,7,26,9,11,7,4,25,23,16,19,11,18,8,20,17,19,8,7,15,22,18,18,4,4,15,3,20,16,15,18,5,23,17,15,7,24,19,6,21,8,25,6,0,6,0,17,25,8,25,14,3,16,6,7,20,21,11,14,11,26,5,16,22,23,4,3,21,24,9,16,5,8,22,5,14,22,23,13,4,22,1,7,11,7,15,5,2,26,20,13,25,26,2,21,23,7,24,17,4,7,7,10,15,2,
			DISCARD: 16,3,25,12,17,2,7,18,10,19,26,25,25,1,25,18,15,24,18,18,18,14,26,16,4,3,24,11,14,12,14,3,16,13,16,6,16,24,25,0,17,25,26,15,26,24,7,15,21,25,6,13,12,5,3,17,9,0,2,23,13,17,0,2,3,17,9,20,14,8,20,5,6,19,20,6,17,1,21,
			CURSE: 6, ESTATES: 3, DUCHY: 6, PROVINCE: 9, GREAT_HALL:12, GARDENS: 2, totalCards: 193

			TEST: 1, FAIL: Player: 1 of 3 players
			Score: 5, Expected: 208, Winner Val Returned: 0, Expected: 1
			HAND: 25,11,6,1,2,
			DECK: 16,1,4,12,15,21,13,17,25,3,0,19,18,8,13,23,15,5,17,21,23,18,16,7,17,17,6,2,23,8,4,12,10,9,25,25,3,12,16,2,15,16,21,7,25,7,3,14,13,20,8,9,11,25,17,2,15,23,4,12,4,9,25,15,18,23,13,22,9,2,24,25,19,19,5,18,0,8,5,13,2,14,23,14,12,13,16,0,10,21,13,15,3,11,3,22,8,17,17,17,19,15,15,12,8,20,3,8,2,9,22,5,23,18,19,9,5,8,10,15,3,23,4,6,7,8,2,15,25,19,6,18,8,21,3,16,15,7,25,18,16,20,23,13,11,16,22,17,24,5,6,1,2,10,8,9,19,10,25,17,2,5,8,11,0,11,0,15,18,25,7,8,19,3,21,3,19,16,21,17,22,0,18,24,11,26,7,3,9,6,20,12,11,2,23,11,
			DISCARD: 13,24,0,5,23,7,13,15,
			CURSE: 7, ESTATES: 3, DUCHY: 11, PROVINCE: 11, GREAT_HALL:9, GARDENS: 5, totalCards: 209

			TEST: 1, FAIL: Player: 2 of 3 players
			Score: -25, Expected: 165, Winner Val Returned: 0, Expected: 0
			HAND: 4,24,13,21,20,
			DECK: 14,13,18,25,13,25,1,23,5,22,9,17,24,6,2,11,4,2,16,0,10,3,15,22,11,8,26,8,22,21,2,9,8,20,7,22,19,9,18,24,4,1,15,1,7,17,12,12,20,2,12,4,5,1,26,16,9,26,25,
			DISCARD: 5,20,0,14,2,20,22,24,13,4,16,10,8,17,26,9,25,16,22,10,9,24,23,13,2,24,13,19,7,12,17,12,5,17,0,8,11,22,5,24,26,21,8,7,12,7,17,11,24,13,21,7,11,18,21,14,15,7,6,23,19,23,9,25,14,9,6,26,4,12,24,4,6,6,11,19,14,2,3,11,16,24,19,0,15,13,14,4,20,20,0,13,17,10,11,5,19,18,4,24,3,2,1,10,8,13,2,23,15,5,7,5,3,0,5,19,13,19,24,6,13,25,20,3,8,5,8,0,23,13,24,0,16,26,11,24,12,13,20,0,19,1,6,22,1,
			CURSE: 9, ESTATES: 7, DUCHY: 9, PROVINCE: 5, GREAT_HALL:6, GARDENS: 5, totalCards: 209

			TEST: 1, PASS: Player: 3 of 3 players
			Score: 0, Expected: 0, Winner Val Returned: 0, Expected: 0
 *
 * int playSmithy(int handPos, struct gameState *state);
 * 	Bug2: Less Cards than expected in hand after card played
 * 	Bug3: Extra card in deck count after card played
 *
 *	Sample Output:
			TEST FOR SMITHY FIRST CARD PLAYED
			FAIL:  Post HandCount Result: 8, Expected: 9
			FAIL:  Post Deck Count: 8, Expected: 7

			TEST FOR DECKCOUNT 0 DISCARDCOUNT 0 test

			TEST FOR MIXED DRAW CARDS DECKCOUNT 197 DISCARDCOUNT 73
			FAIL:  Post HandCount Result: 8, Expected: 9
			FAIL:  Post Deck Count: 195, Expected: 194

			TEST FOR ALL COINS IN DECK AND DISCARD
			FAIL:  Post HandCount Result: 5, Expected: 6
			FAIL:  Post Deck Count: 2, Expected: 1
 *
 * int playAdventurer(struct gameState *state);
 * 	Bug4: Adventurer card not put on played pile
 * 	Bug5: Extra Card in hand after card played
 *
 * 	Sample Output:
			TEST FOR ADVENTURER FIRST CARD PLAYED
			Test 0: FAIL: HandCount: 9, Expected: 8
			Test 0: FAIL: playedCardCount: 0, Expected: 1
			Test 0: FAIL: playedCard: 0, Expected: 7
			Test 0: PASS: Coins discarded: Gold: 0, Silver: 0, Copper: 0

			TEST FOR DECKCOUNT 0 DISCARDCOUNT 0 test
			Test 0: FAIL: HandCount: 4, Expected: 3
			Test 0: FAIL: playedCardCount: 0, Expected: 1
			Test 0: FAIL: playedCard: 0, Expected: 7
			Test 0: PASS: Coins discarded: Gold: 0, Silver: 0, Copper: 0

			TEST FOR MIXED DRAW CARDS DECKCOUNT 197 DISCARDCOUNT 73
			Test 0: FAIL: HandCount: 9, Expected: 8
			Test 0: FAIL: playedCardCount: 0, Expected: 1
			Test 0: FAIL: playedCard: 0, Expected: 7
			Test 0: PASS: Coins discarded: Gold: 0, Silver: 0, Copper: 0

			TEST FOR NO COINS IN DECK OR DISCARD
			Test 0: FAIL: HandCount: 4, Expected: 3
			Test 0: FAIL: playedCardCount: 0, Expected: 1
			Test 0: FAIL: playedCard: 0, Expected: 7
			Test 0: PASS: Coins discarded: Gold: 0, Silver: 0, Copper: 0

 *
 * Baron Card using CardEffect
 * 	Bug7: Baron card not put onto played pile
 * 	Bug8: Extra Card in hand after card played
 * 	Bug9: Coin Bonus being not being updated
 * 	Bug10: Coins added to state->coins which is wiped before coins updated in playCard() function
 * 	Bug11: Estate supply loses more estates than expected when estate taken from supply
 *
 * Sample Output:
			TEST FOR ESTATE IN HAND, ESTATE SUPPLY > 1, CHOOSE COINS
			FAIL: Post Hand Baron Count: 1, Expected: 0
			FAIL: Last Card Played: 0, Expected: 15
			FAIL: playedCardCount: 0, Expected: 1
			FAIL: Hand Count: 6, Expected: 5
			FAIL: Coin bonus returned: 0, Expected: 4
			FAIL: Testing Values haven't changed: Coins updated to: 4, Expected: 0

			TEST FOR ESTATE IN HAND, ESTATE SUPPLY > 1, CHOOSE EXTRA ESTATE
			FAIL: Post Hand Baron Count: 1, Expected: 0
			FAIL: Last Card Played: 0, Expected: 15
			FAIL: playedCardCount: 0, Expected: 1
			FAIL: Hand Count: 4, Expected: 3
			FAIL: Estate Supply Count: 10, Expected: 11

			TEST FOR 0 ESTATE IN HAND, ESTATE SUPPLY > 1, CHOOSE COINS
			FAIL: Post Hand Baron Count: 1, Expected: 0
			FAIL: Last Card Played: 0, Expected: 15
			FAIL: playedCardCount: 0, Expected: 1
			FAIL: Hand Count: 10, Expected: 9
			FAIL: Estate Supply Count: 10, Expected: 11

			TEST FOR 0 ESTATE IN HAND, ESTATE SUPPLY > 1, CHOOSE ESTATE
			FAIL: Post Hand Baron Count: 2, Expected: 1
			FAIL: Last Card Played: 0, Expected: 15
			FAIL: playedCardCount: 0, Expected: 1
			FAIL: Hand Count: 6, Expected: 5
			FAIL: Estate Supply Count: 10, Expected: 11

			TEST FOR ESTATE CARD IN HAND, ESTATE SUPPLY = 0, CHOOSE TAKE ESTATE
			FAIL: Post Hand Baron Count: 3, Expected: 2
			FAIL: Last Card Played: 0, Expected: 15
			FAIL: playedCardCount: 0, Expected: 1
			FAIL: Hand Count: 9, Expected: 8

			TEST FOR ESTATE CARD IN HAND, ESTATE SUPPLY = 1, CHOOSE TAKE ESTATE
			FAIL: Post Hand Baron Count: 2, Expected: 1
			FAIL: Last Card Played: 0, Expected: 15
			FAIL: playedCardCount: 0, Expected: 1
			FAIL: Hand Count: 8, Expected: 7
			FAIL: Estate Supply Count: -1, Expected: 0

			TEST FOR 0 ESTATE IN HAND, ESTATE SUPPLY = 0, CHOOSE COINS
			FAIL: Post Hand Baron Count: 1, Expected: 0
			FAIL: Last Card Played: 0, Expected: 15
			FAIL: playedCardCount: 0, Expected: 1
			FAIL: Hand Count: 9, Expected: 8

 * Tribute card using CardEffect
 * 	Bug12: More actions than expected sometimes added
 * 	Bug13: Tribute Card not added to played pile
 * 	Bug14: Extra Card in hand after card played
 * 	Bug15: Next Player's cards not put onto the discard Pile after being shown
 * 	Bug16: Next Player's card are not removed from their deck after being shown
 * 	Bug17: Added coins for treasure cards revealed not added to bonus
 * 	Bug18: Added coins for treasure cards added to state->coins which is wiped before coins updated in playCard() function
 *
 * 	Sample Outputs:
			Card1: 0 - Dead, Card2: 0 - Dead (-1 indicates card not drawn)
			**Game State Checks Starting**
			TEST1 FAIL: Reported total Actions: 7, Expected total Actions: 1 (Control: 1, Bonus Actions Calculated: 0)
			TEST1 FAIL: Reported playedCardCount: 0, Expected: 1 (Control: 0, Cards Played: 1)
			TEST1 FAIL: Reported last playedCard: 0, Expected: 19
			**Next Player Checks Starting**
			TEST1 FAIL: Reported discardCount: 0, Expected: 2 (Control: 0 + Revealed Card(s): 2)
			TEST1 FAIL: Reported deckCount: 6, Expected: 8 (Control: 10 - Revealed Card(s): 2 (Expected may include Discard: 0)
			**Current Player Checks Starting**
			TEST1 FAIL: Reported handCount: 5, Expected: 4 (Control: 5 - 1 + Bonus Cards: 0)
			TEST1 FAIL: Hand index where tribute was: 19, Expected: 4 (last card from original hand)

			 Card1: 4 - Treasure, Card2: 5 - Treasure (-1 indicates card not drawn)
			**Game State Checks Starting**
			TEST8 FAIL: Reported total Actions: 5, Expected total Actions: 1 (Control: 1, Bonus Actions Calculated: 0)
			TEST8 FAIL: Reported Bonus Coins: 0, Expected: 4
			TEST8 FAIL: Reported playedCardCount: 0, Expected: 1 (Control: 0, Cards Played: 1)
			TEST8 FAIL: Reported last playedCard: 0, Expected: 19
			**Next Player Checks Starting**
			TEST8 FAIL: Reported discardCount: 0, Expected: 2 (Control: 0 + Revealed Card(s): 2)
			TEST8 FAIL: Reported deckCount: 6, Expected: 8 (Control: 10 - Revealed Card(s): 2 (Expected may include Discard: 0)
			TEST8 FAIL: Reported Last Discard: 0, Expected: 5 (Control: Second Revealed Card: 5)
			**Current Player Checks Starting**
			TEST8 FAIL: Reported handCount: 5, Expected: 4 (Control: 5 - 1 + Bonus Cards: 0)
			TEST8 FAIL: Hand index where tribute was: 19, Expected: 4 (last card from original hand)
			TEST8 FAIL: Changes not in scope:  gameState->coins changed

 * Baron Card random check - additional bugs
 * 	Bug19: Estate not added to discard pile when choice is to take an estate
 *		(Estate should be taken from supply if there are estates and added to discard)
 *
 *  Sample Output:
			Test: 0, choice: 0, hand estates: 0, handCount: 3, estate supply: 2
			Test: 0 FAIL: Post Hand Baron Count: 1, Expected: 0
			Test: 0 FAIL: Last Card Played: 0, Expected: 15
			Test: 0 FAIL: playedCardCount: 0, Expected: 1
			Test: 0 FAIL: Hand Count: 3, Expected: 2
			Test: 0 FAIL: Estate not discarded.  Last discard: 9, Expected: 1, control estate supply: 2, control estates in hand: 0, active estate supply: 0, active estates in hand: 0
			Test: 0 FAIL: Estate not added to DiscardCount.  DiscardCount: 196, Expected: 197, control estate supply: 2, control estates in hand: 0, active estate supply: 0, active estates in hand: 0
			Test: 0 FAIL: Estate Supply Count: 0, Expected: 1

			Test: 7, choice: 1, hand estates: 1, handCount: 5, estate supply: 5
			Test: 7 FAIL: Post Hand Baron Count: 1, Expected: 0
			Test: 7 FAIL: Last Card Played: 0, Expected: 15
			Test: 7 FAIL: playedCardCount: 0, Expected: 1
			Test: 7 FAIL: Hand Count: 4, Expected: 3
			Test: 7 FAIL: Coin bonus returned: 0, Expected: 4
			Test 7: FAIL: gameState->coins Reported: 8, Expected: 4

 *
 * playAdventurer random check - additional bugs
 * 	Bug20: When there are less than two treasures between the deck and the discard pile - segmentation fault
 *
 * 	Note:  To get prior bug faults to report Segmentation fault was fixed and then reverted to
 * 	original upon completion.
 *
 * Sample Output:
		./randomtestadventurer >> randomtestadventurer.out
		Segmentation fault (core dumped)
		make: *** [randomtestadventurer.out] Error 139
 */

