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