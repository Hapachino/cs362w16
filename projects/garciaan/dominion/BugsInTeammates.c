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
	- Suspected to start within the hand effects


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












