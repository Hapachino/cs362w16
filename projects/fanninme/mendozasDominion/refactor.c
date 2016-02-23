Bugs introduced

playAdventurer: Reveals cards until 3 treasure cards are revealed. Changed 
while(drawntreasure<2) to while (drawntreasure<=2).

playSmithy: Player draws 2 cards instead of 3. Changed for (i = 0; i < 3; i++)
to for (i = 1; i < 3; i++)

playVillage: Village card is trashed instead of discarded. Changed 
discardCard(handPos, currentPlayer, state, 0) to discardCard(handPos, 
currentPlayer, state, 1). Trashflag changed.

playSteward: Instead of trashing a card from the player's hand, one is discarded 
while the other is trashed. Changed  discardCard(choice2, currentPlayer, state, 
1) to  discardCard(choice2, currentPlayer, state, 0). Changed trashFlag.

playSalvager: Additional coin is added. Changed state->coins = state->coins + 
getCost( handCard(choice1, state) ) to state->coins = state->coins + getCost( 
handCard(choice1, state) )+1.
