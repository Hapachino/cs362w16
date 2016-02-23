/********************************
Fixing bugs found by my teammates

Bug #1  The adventurer card is not actually being discarded from the player's hand
Reported by Jim Linnenburger
Found in: Adverturer Card Test
Fix: 
	This was an error that I had introduced. I fixed the while loop in the refactored
	playAdventurer() function.
	
******************************************************************************	
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

******************************************************************************
Bug #3 The smithy card is being sent to the trash instead of the played card pile.
Reported by Jim Linnenburger
Found in: Smithy Card Test
Fix:
	This is the bug I introduced during refactoring. I changed the trashFlag to 0 and 
	now the card gets discarded.
	
******************************************************************************
Bug #4 isGameOver() does not check the supply counts for card #25 (sea hag) or
   card #26 (treasure map) in its check for 3 empty supply counts.
Reported by Jim Linnenburger
Found in: isGameOver Function Test
Fix:
	The function checked supply counts and had hardcoded the number 25 as the max 
	treasure card value. I changed this to one more than the last treasure card, treasure_map.
	This fixed the issue of not checking sea_hag and treasure_map but would have to be changed 
	if new cards were ever introduced.
	
******************************************************************************
Bug#5 Estate Supply Count Incorrect
Reported by Jason Ridder
Found in: playing an Estate Card
Fix:
	The first mistake I saw in the dominion code is that the baron card calls for gaining an estate
	card but will then decrement the supply count aftwards. The gain card function already decrements
	the supply count so it was being done twice. This fixed many errors.
	However, I still get errors that state the supply count is one fewer than it should be when an estate card
	is not present. When an estate card is not in the hand, the player gains an estate card. The test does not seem
	to account for the gaining of the card as seen here in the test:
		  if(choice1 == 1 && (estateInHandRand != estate)){
				if(DEBUG3) {
				   printf("ESTATE CARD NOT FOUND---\n");
				   
				  if(G.supplyCount[estate] != supplyRandomEstate)
					   printf("TEST FAIL\n");
				   ..
				}
				...
		  }
	the supplyRandomEstate should have been increased by 1. This solves a mislabeled bug. The last bug is that the
	tester did account for the player to gain a card in this situation but expected it to go in the hand. Therefore,
	when checking the hand supply count, the tests showed the count was one fewer than expected. The dominion
	card, by default, was putting the gained card into the discard pile. I fixed this by changing the toFlag in gainCard()
	to put it into the hand.
	
	Finally, there were still errors appearing. I noticed this line in the test with the following comment:
			if(randomNum != estate) { //make sure inital hand never gets an estate, it will be added later
				G.hand[G.whoseTurn][i] = 2;//just make it a duchy card
			}
	This was called when filling in random cards to the hand. The problem is is that the comment conflicts with the logic.
	It's obvious that if the randomNum turned out to be an estate, the test should use a duchy card instead. When making
	this change and testing again, I see that the bugs that did exists before are no longer there.

******************************************************************************	
Bug#6 Players are not discarding copper cards from thier hands. 
Reported by Jason Ridder
Found in: playing a cutpurse Card
Fix:
	The curpurse case in card effect looked like it should function perfectly to me. After stepping
	through it in gdb, I realized that it WAS working correctly and discarding a copper. The issue was
	actually with my teammate's test. Here is a snippet of the part where he sets up the test:
	
	             //Fill other players hands with 5 copper cards
				 for(j=0;j < numPlayer;j++) {
					if(j != whoseTurnIsIt) {
					for (i = 0; i < 6; i++) {
					   G.hand[j][i] = copper; //copper
					}
					G.handCount[j] = 5;
					}
				 }
	He means to setup players other than current player with 5 copper cards but his for loop actually 
	loops six times. When he checks for errors with this snippet:
						printf("           Player %d had %d copper card, expected 4\n", j+1, countCopper);
                         if(countCopper != 4)
                            printf("               TEST FAILED\n");
	I see that the number 4 is hardcoded in. So I had 6 copper cards and 1 was discarded for a final 
	total of 5 but the card test was erroneously checking for 4, which I am confident is an incorrect
	assumption. Therefore, no bug needs to be fixed in the code.
	
******************************************************************************	
Bug #7 Bug found on test 4. Function doesn't work correctly with card piles sea_hag and treasure_map run to zero.
Reported by Jason Ridder
Found in: isGameOver Function Test
Fix:
	This was the same bug found by my other teammate and so I had fixed it already by expanding
	the for loop that checks supply counts to count all treasure cards up to treasure_map.
*********************************/