/********************************
Fixing bugs found by my teammates

Bug #1  The adventurer card is not actually being discarded from the player's hand
Reported by Jim Linnenburger
Found in: Adverturer Card Test
Fix: 
	This was an error that I had introduced. I fixed the while loop in the refactored
	playAdventurer() function.
	
Bug #2 Discarded cards do not match up with expected values. 
 Description:
          There is an estate card (#1) that is missing at the end. Before the
          adventurer card is played, there are 3 total estate cards in the hand
          and deck.  Afterwards, there are only 2 in the hand/deck/discard.
  Example test output:
		-------------------------------------------------------------
		TEST 1: At least 2 treasure cards in player's deck
		-------------------------------------------------------------
		Starting hand: [4, 1, 4, 4, 7]
		Starting deck: [4, 4, 1, 1, 4]
		Starting discard: [ ]
		# coin cards: 3
		After adventurer card has been played:
				   Cards in hand: 7 [6 expected]
				   Cards in deck: 1 [1 expected]
				Cards in discard: 1 [3 expected]
		Player's hand: [4, 1, 4, 4, 7, 4, 4]
		Expected hand: [4, 1, 4, 4, 4, 4]
		Player's deck: [4]
		Expected deck: [4]
		Player's discard: [1]
		Expected discard: [ 7, 1, 1]
				Gamestates equal: 0
		-------------------------------------------------------------
		TEST 1 STATUS:  **** FAILURE **** FAILURE **** FAILURE ***
		-------------------------------------------------------------
Reported by Jim Linnenburger
Found in: Adverturer Card Test
Fix:
	While trying to fiix this, I added discardCard() at the end of the playAdventurer function.
	This fixed part of the issue.  But there were still cards in discard that should be in played cards.
	After looking at what the discard function does, I realized the fix was to set the cards in the 
	temp hand to the play cards and that fixed the missing estate card and discarded counts issue.


Bug #2 The smithy card is being sent to the trash instead of the played card pile.
Reported by Jim Linnenburger
Found in: Smithy Card Test
Fix:
	This is the bug I introduced during refactoring. I changed the trashFlag to 0 and 
	now the card gets discarded.

Bug #3 isGameOver() does not check the supply counts for card #25 (sea hag) or
   card #26 (treasure map) in its check for 3 empty supply counts.
Reported by Jim Linnenburger
Found in: isGameOver Function Test
Fix:
	The function checked supply counts and had hardcoded the number 25 as the max 
	treasure card value. I changed this to one more than the last treasure card, treasure_map.
	This fixed the issue of not checking sea_hag and treasure_map but would have to be changed 
	if new cards were ever introduced.

*********************************/