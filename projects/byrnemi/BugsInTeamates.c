 /*

Michael Byrne
ONID: byrnemi
2 - 28 - 2016
SE 2, Assignment 5


Tests for Dominion code: Eric Anderson
 


  Unit Test 1: getCost()
  	No bugs detected.
  Unit Test 2: updateCoins()
  	No bugs detected.
  Unit Test 3: handCard()
  	No bugs detected
  Unit Test 4: isGameOver()
  	No bugs detected.


  Card Test 1: Smithy
  	Bug 1.1: Function results in a mismatch from expected card counts in both deck and hand. 
  	Smithy should leave 47 cards in deck after play, results in 46. Hand should have 52 cards
  	but has 53. This can be traced to the for loop in the playSmithy() function, where the
  	drawCard() function is called four times and not three because the condition is 
  	"<= 3" rather than "<3." This seems to be the root bug and is different than the 
  	cards documented bug. **To recreate**: Run any hand/deck/discard combination with a 
  	sufficient number of cards in each pile to draw four cards. 

  Card Test 2: Adventurer
  	Note: CardTest4 has a bug itself. It fails to account for situations in which the combined
  	deck and discard piles do not have more than one treasure between them. In running batches of 
  	200 tests, this does happen. But it should be disregarded. 
  	Otherwise, no bugs were detected. I attempted to find the advertised bug in this card, 
  	but no such luck. It may not be there. At the end of each simulated game, I was found
  	the anticipated number of total cards among all of the piles (hand, deck, discard).
  Card Test 3: Cutpurse
  	No bugs detected.
  Card Test 4: Salvager
  	Bug 1.1: I detected this bug when I tested my own code with this function and it reppears here. 
  	The problem is that if the card is fed a player choice of "0" the program interprets this 
  	choice as "no choice" rather than the card indexed at "0." With a random 50 card hand, this 
  	happens with about .02 probability. Significant. **To recreate:** Give the playCard function 
  	a player choice of 0, note what card is at the 0 position in the player hand, and then counts
  	instances of that card in the player hand before and after the card is played. They should 
  	be different, when card removed, but they will be the same. 

Tests for Dominion code: Matthew Ailes

Unit Test 1: getCost()
    No bugs detected.
  Unit Test 2: updateCoins()
    No bugs detected.
  Unit Test 3: handCard()
    No bugs detected
  Unit Test 4: isGameOver()
    No bugs detected.


  Card Test 1: Smithy
    No bugs detected. On inspection, the advertised bug (where smithy returns 1 rather than 0)
    is not present in the current code. I would not have caught the bug in any case, as my 
    test only checks bad return values, not correct ones. 


  Card Test 2: Adventurer
    Test bug 1.1 The advertised bug for playAdventurer() did not seem to be present. I did, however, 
    find a test bug. It is rarely the case that my random deck features 0 treasures, 
    but it does happen. The reason for this is that my test only counts treasure 
    cards appearing in the deck, neglecting the random discard pile. So, while I wind up with
    every deck card flipped, the card action will correctly search the discard pile. This is a scenario
    that is almost but not quite impossible in normal gameplay.
  
  Card Test 3: Cutpurse
    No bugs detected
  Card Test 4: Salvager
    Bug 4.1 As I wrote in the bug report for teammate 1:
        Bug 1.1: I detected this bug when I tested my own code with this function and it reppears here. 
    The problem is that if the card is fed a player choice of "0" the program interprets this 
    choice as "no choice" rather than the card indexed at "0." With a random 50 card hand, this 
    happens with about .02 probability. Significant. **To recreate:** Give the playCard function 
    a player choice of 0, note what card is at the 0 position in the player hand, and then counts
    instances of that card in the player hand before and after the card is played. They should 
    be different, when card removed, but they will be the same. 
    No other bugs detected.