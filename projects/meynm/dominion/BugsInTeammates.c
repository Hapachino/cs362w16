/******************************************************************************
BugsInTeammates.c
by Matthew Meyn
2016/2/22



*******************************************************************************
Bugs in Teammate 1's dominion.c
*******************************************************************************

Bug #1

Title: 	smithy card causes player to draw wrong number of cards

Classification: Severe

Platform: 	Linux 
			3.13.0-74-generic #118-Ubuntu SMP

Description:

	My tests indicate that the active player's handCount in the post-test game 
	state is one greater than it should be. It would therefore appear that the 
	player is drawing 4 cards when the smithy card is played.
	
	The expected result of the smithy card is that the player should draw 
	exactly 3 cards. So, apparently, the smithy card must be causing the player 
	to draw too many cards.

Conditions to reproduce:
 
	Initialize a new game state with initializeGame(), using 2, 3 or 4 players.
	Choose a player, and a hand position in that player's hand. Call 
	playSmithy() with these parameters. For example:
	
		game with 2 players, player 0 plays Smithy
	
*******************************************************************************

Bug #2

Title: 	After playSmithy(), player loses a card

Classification: Severe

Platform: 	Linux 
			3.13.0-74-generic #118-Ubuntu SMP

Description:

	  When adding up all the player's cards from every pile, the player has one
	  fewer card in the post- state than in the pre- state. This is contrary to
	  what would be expected, given that the player should neither gain nor 
	  lose cards from the total cards in player's possession when playing this 
	  card.
	  
Conditions: 

	  Same as Bug #1. Another example:
	  
	  		game with 4 players, player 2 plays Smithy
			
*******************************************************************************

Bug #3

Title: 	When playing adventurer, the player sometimes gains and/or loses cards

Classification: Severe

Platform: 	Linux 
			3.13.0-74-generic #118-Ubuntu SMP

Description:

		Sometimes when playAdventurer() is called, when the cards in all the 
		active player's piles are added up, there are fewer cards in the post-
		state than in the pre- state. The count can be different by one or more
		cards. 
		
		This is different from the expected result, which is that the total 
		count of all the player's cards should not be changed. The adventurer
		card should only cause the player to draw some cards from the player's
		own deck, two of which should end up in the player's hand, and any 
		others should end up either in deck or discard piles.
		
Conditions: 

		Here are preconditions for a failure case:

			numPlayers=2, random seed=1455859881, player=0

			Pre-game hand:
				4	4	4	1	4	Count: 5
			Pre-game deck:
				4	1	4	4	1	Count: 5
			Pre-game discard:
									Count: 0
								
								
								
								
*******************************************************************************
Bugs in Teammate 2's dominion.c
*******************************************************************************

Bug #1

Title: 	After playing adventurer, the player's deck contains different cards

Classification: Severe

Platform: 	Linux 
			3.13.0-74-generic #118-Ubuntu SMP

Description:

		Often, after playing the adventurer card, the total set of cards in the
		player's possession (among all piles) is altered. This is contrary to
		what would be expected, since the adventurer card only draws cards from
		the player's own deck. More specifically, it appears that when the last
		two cards in the pre-test player's deck do not happen to be treasure 
		cards, the post- player has gained a treasure card that seems not to 
		have come from that player's deck. Example below.
		
Conditions to reproduce:

		Set up a game state as follows:
		
			numPlayers=4, seed=1000
			
			Pre-game hand:
				(empty)
			Pre-game deck:
				1	1	4	4	4	4	4	4	4	1		Count: 10
			Pre-game discard:
				(empty)

		Call adventurerEffect() with these parameters:
		
			currentPlayer = 2
	
	
	
			
		The resulting post-conditions should look like this:
	
			post-game hand:
				4	4								Count: 2
			post-game deck:
				1	1	4	4	4	4	4	4		Count: 8
			post-game discard:
				(empty)

As can be seen, it appears as though one Estate card (enum 1) has been 
transformed into a copper card (enum 4).
	
******************************************************************************/  	
	  	
