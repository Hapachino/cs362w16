/*

BUG REPORTS


bug.fullDeckCount.1
	Makes it so not all cards in a players discard hand and deck are added together properly
	Bug always happens, unless your whole deck is one specific card and you are counting that card
		- when calling fullDeckCount the second parameter is a card paramater 
			- this checks for that card rather than every card and keeps a count of it
	Estimated Severity: High
	Estimated Proiority: High


bug.scoreFor.1
	Makes it so gardens are incorrectly scored in the game
	Bug happens anytime at least one gardens in in the deck, but happens for each one present
		- scoreFor calls fullDeckCount to calculate score for a garden which produces incorrect result
		- if people have gardens in their deck their score will not be correct
	Estimated Severity: High
	Estimated Priority: High

bug.scoreFor.2
	Inproperly adds cards from the discard pile to the score
	Whenever there are scoring cards in the discard pile
	Estimated Severity: High
	Estimated Priority: High

bug.scoreFor.3
	Improperly adds score cards from deck pile all are ignored
	Whenever there are scoring cards in the deck pile
	Estimated Severity: High
	Estimated Priority: High

bug.smithy.1
	Makes smithy draw one extra card
		- this bug does not break the game, just makes smithy run incorrectly
	Bug happens anytime smithy is played		
	Estimated Severity: Average
	Estmated Priority: Average

bug.adventurer.1
	When adventurer is played card is not discarded, causing playedCardCount to not increment and playedCards to not be updated
		- Adventurer remains in hand and could be played again depending on num actions
	Bug happens anytime the adventurer is played
	Estimated Severity: High
	Estimated Priority: High

bug.adventurer.2
	When adventurer is played any silvers that are drawn are not countded as drawnTreasure for the limit of 2 treasure
	Happens whenever adventurer is played and at least one silver is drawn from the deck
	Estimated Severity: Average
	Estimated Priority: Average

bug.council_room.1
	When council room is played the player does not recieve another buy action
	Happens whenever council room is played
	Estimated Severity: Average
	Estimated Priority: Average

bug.remodel.1
	When playing remodel it is incorrectly counted as being played
	Happens if choice1 price is not within 2 of choice2 which should just exit out, but instead the card is still being played with no effect besides losing the card
	Estimated severity: Low
	Estimated Priority: Low

bug.remodel.2
	When playing remodel supply count is not being changed for the card being gained in choice2
	Happens when choice 2 is a valid target, the supply count is not lowered for that supplypile
	Esitmated Severity: Average
	Estimated Priority: Average




















*/
