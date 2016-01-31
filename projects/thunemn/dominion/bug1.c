Tests Ran:

	I developed and ran tests for the following functions:
		-updateCoins
		-isGameOver
		-getCost
		-gainCard
	I developed and ran tests for the following cards:
		-Smithy
		-Adventurer
		-Village
		-Great Hall

I found no bugs for updateCoins, isGameOver, getCost, or gainCard.

Smithy Card:
	The Smithy Card effect does not discard cards correctly.  I believe
	that this is not due to a bug in the Smithy Card effect, but in the 
	discardCard function.  Instead of adding a card to the discard pile 
	and incrementing the discardCount, the discardCard function adds the 
	card to the playedCards array and increments the playedCardCount.

Adventurer Card:
	The Adventurer Card effect does not call the discardCard function, 
	so it is not susceptible to the same bug as the Smithy Card.  The
	Adventurer Card manually adds all crads drawn into the discard pile
	itself.

Village Card:
	Like the Smithy Card effect, the Vilalge Card effect calls the 
	discardCard function, leading to the same bug.

Great Hall Card:
	Like the Smithy Card effect, the Great Hall Card effect calls the 
	discardCard function, leading to the same bug.