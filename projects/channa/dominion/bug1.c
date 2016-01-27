Nancy Chan
CS 362
Winter 2016
Assignment 3: bug1.c

Bugs found:

scoreFor():
	unittest4 detected a bug in the calculation of the gardens effect. A gardens card is worth
	1 victory point for every 10 cards in the player's deck (the player's discard pile and hand
	are a part of the player's deck at that point) rounded down. Instead of counting all of the
	player's cards and then dividing by 10. scoreFor() uses fullDeckCount() to only get the
	player's total number of curse cards and then dividing by 10.

	unittest4 also detected a bug in the score calculation of the player's deck. scoreFor() fails
	to consider cards in the player's deck when the player's discard pile count is zero.

playSmithy():
	cardtest1 detected incorrect counts of the player's cards after playing smithy. Instead of 7
	cards in the deck, there were 6. Instead of 8 cards in the hand, there were 9. This means that
	there was an extra card in the hand and one missing card from the deck and so smithy drew 4
	cards instead of 3 since the other player's cards, victory card piles, and kingdom card piles
	were unaffected.
	
	Additionally, the discard pile was empty which means that after being played,
	smithy was trashed rather than discarded.

playAdventurer():
	cardtest2 detected that non-treasure cards revealed are not properly discarded. They could not be
	accounted for in either the player's own piles nor the other player's piles. Instead of being
	discarded, it seems that they have been removed from play.
