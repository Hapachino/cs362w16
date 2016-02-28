Loomisc: 

Bug 1:

	Village card gains 1 action

	dominion.c
	
	function: playVillage()
	
	Severity:  Severe

	Method: 
		Start a game of dominion
		play a village card 

	Unit test shows that the village card gains 1 action after completion.

	The expected action is that the village card gains 2 actions after completion.

	This is a severe bug as while it does not crash the system, it reproduces every time and can greatly affect the game.

Bug 2: 

	Smithy card gains 4 cards instead of 3

	dominion.c
	
	function: playSmithy()
	
	Severity:  Severe

	Method: 
		Start a game of dominion
		play a smithy card 

	Unit test shows that the smithy card gains 4 cards after completion.

	The expected action is that the smithy card gains 3 cards after completion.

	This is a severe bug as while it does not crash the system, it reproduces every time and can greatly affect the game.

Thunemr: 

Bug 1:
	Salvager card did not update coins properly

	dominion.c
	
	function: playSalvager()
	
	Severity:  Severe
	
	Method: 
		Start a game of dominion
		play a salvager card 

	Unit test shows that the salvager card does lead to the user gaining one coin higher than the worth of the card that is discarded.

	The expected action is that post salvager card the user will have the amount of coins equal to the value of the card that they choose to discard. 

	This is a severe bug as while it does not crash the system, it reproduces every time and can greatly affect the game.

Bug 2: 
	Village card did not discard played card properly 

	dominion.c
	
	function: playVillage()
	
	Severity:  Severe

	Method: 
		Start a game of dominion
		play a village card 

	Unit test shows that the village card is not returned to the discard pile and is instead trashed.

	The expected action is that post village card the discard deck will contain the played village card. 

	This is a severe bug as while it does not crash the system, it reproduces every time and can greatly affect the game.