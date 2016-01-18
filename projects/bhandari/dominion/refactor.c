#Documentation.c
#Rishi Bhandarkar
#CS 362

#Refactor.c

- The Smithy, Adventurer, Village, Feast, and Council Room card effects were moved from the cardEffects function to their own functions
	- playAdventurer
	- playSmithy
	- playVillage
	- playFeast
	- playCouncil_Room
- playAdventurer: in the first while loop, set condition to drawnTreasures <= 2, which incorrectly draws an additional treasure
- playSmithy: in the for loop, set the conditional to i <= 3 which incorrectly makes the player draw an additional 4th card 
- playVillage: incorrectly increments the numActions attribute by 3, allowing for an additional action
- playFeast: incorrectly backs up the hand, set conditional in for loop to < instead of <= state->handCount[currentPlayer]
- playCouncil_Room: incorrectly decrements the numBuys attribute instead of incrementing it
