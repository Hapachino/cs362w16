Play Smithy:
	1. When Smithy card is played loop 3 times.
	2. Each loop iteration draws a card using the drawCard function for the current player
	3. Finally, discard the smithy card from the current players deck

Play Adventure:
	1. First loop iterates through the player's deck until two treasure cards are found (copper, silver, gold). If deck is empty then the deck is shuffled.
	2. If not a treasure card add card to temporary hand. Then remove not tresure card from players hand.  
	3. The second loop discards temp hand cards into players played pile.

discardCard()
	1. Check if card has not been destroyed (removed from game)
	2. If not add the card to the players played pile
	3. Played card set to -1 to make unusable.
	4. If last card in hand or only card in hand subtract one from player hand count.
	5. Else use last card in hand to replace discarded card in hand position then invalidate last card and subtact 1 from hand count.

updateCoins()
	1. Function parameters are current player, state of game and bonus coins.
	2. Reset coin count to zero
	3. Iterate through players hand adding coins based on value of the player's treasure cards.
	4. Add bonus coins.