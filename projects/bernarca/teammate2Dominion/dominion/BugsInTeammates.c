/*
teammate1Dominion: bernarca
Test Results:
	Unit Test 1: updateCoins
		Always correct

	Unit Test 2: discardCard
		Always correct

	Unit Test 3: whoseTurn
		Always correct

	Unit Test 4: endTurn
		Occasionally correct. Always player 0's turn.

	Card Test 1: Adventurer Card
		Never worked correctly. Always above the max limit.

	Card Test 2: Smithy Card
		Segmentation fault

	Card Test 3: Village Card
		Occasionally correct. Errors due to one less action than expected.

	Card Test 4: Salvager Card
		Never worked correctly. Coins always returned as 0.		


teammate2Dominion: colvinch
Test Results:
	Unit Test 1: updateCoins
		Always correct

	Unit Test 2: discardCard
		Always correct

	Unit Test 3: whoseTurn
		Always correct

	Unit Test 4: endTurn
		Occasionally correct. Turn always returns 0.

	Card Test 1: Adventurer Card
		Never worked correctly. Might be issue with my test code though.

	Card Test 2: Smithy Card
		Never worked correctly. For most cases, hand count is one less. Exception to this is when expected is 2, returns 0.

	Card Test 3: Village Card
		Occasionally correct. When error, num actions is 1 when expecting 2

	Card Test 4: Salvager Card
		Never worked correctly. Coins are always 0.


teammate3Dominion: hickej
Test Results:
	Unit Test 1: updateCoins
		Always correct

	Unit Test 2: discardCard
		Always correct

	Unit Test 3: whoseTurn
		Always correct

	Unit Test 4: endTurn
		Occasionally correct. Turn always retuns 0.

	Card Test 1: Adventurer Card
		Never correct. Hand card always greater than max limit.

	Card Test 2: Smithy Card
		Never correct. Hand count results is always 2 less than expected.

	Card Test 3: Village Card
		Correct for most of the tests. One exception: Num actions was 1 instead of 2.

	Card Test 4: Salvager Card
		Never correct. Coin results always returns 0.
*/