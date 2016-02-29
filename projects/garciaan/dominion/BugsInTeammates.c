----------------- TEAMMATE 1 -----------------
TESTED:
- playSmithy
- playAdventurer
- drawCard
- updateCoins
- gainCard
- buyCard

FAILED TESTS:
- Smithy
	- Hand Effects 
	- Played Card Effects
- Adventurer
	- All Tests

---- Bug Fixes ----
-- Smithy --
- Cause: Discard immediately after draw each time
- Fix: Move discard after drawing 3 cards and only do once
- Result: Hand effects still fail
- Cause: Test accidentally tested for deck result, not hand result
- Fix: Searched hand, not deck for the drawn cards
- Result: All passing

-- Adventurer --
- Cause: the drawn card is not known, so there is a semi infinite loop
because it cannot tell if a coin is drawn and therefore discards it
immediately
- Fix: set the cardDrawn variable to the last card drawn
- Result: Hand Effects and played card effects still fail
- Cause: Adventurer does not get discarded after played
- Fix: Added hand position parameter to function to be 
able to discard the adventurer card from hand
- Result: Scenario of No treasure in deck still fails
- NOTE: Known bug with original dominion fail
- Cause: Infinite loop caused by function not knowing that
it has gone through all the cards
Fix: Checked if discard pile was empty before shuffle attempt
Result: All passing

----------------- TEAMMATE 2 -----------------
TESTED: 
- playSmithy
- playAdventurer
- playGreat_Hall
- playVillage
- drawCard
- updateCoins
- gainCard
- buyCard

FAILED TESTS:
- Smithy
	- Nothing else affected
- Adventurer
	- Played Card Affects
	- Scenario: Less than 2 treasure available
- playGreat_Hall
	- Hand effects
	- Played Card effects
	- Nothing else affected

---- Smithy ----
- Smithy appears to be affecting more than it should, but it also does everything
it should.

---- Adventurer ----
- It seems that adventurer card does not get correctly discarded.
- When there are less than 2 treasure available to draw, the deck does
not get correctly affected.
- Adventurer checks for more than just treasures

---- Great Hall ----
- Great hall does not seem to properly perform its actions to the players hand
- Great hall seems to affect more than it should












