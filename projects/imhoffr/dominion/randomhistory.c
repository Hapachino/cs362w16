/*********************
 Regina Imhoff
 CS 362
 imhoffr@oregonstate.edu
 Assignment 4 randomhistory.c
 
 Adventurer:
 
 For testing adventurer, I intialized the game in a similar way to how I initialized the unit/card tests.
 Because this was to be done randomly, I made the initialization more generic - fewer options hard coded
 into the initialization.  
 
 Players are randomly assigned random decks.  Adventurer is played and x many cards are drawn until 
 2 coins have been acquired by the player.  The card is then discarded.
 
 A new bug was found with the random tester: After the first run, the second run found that the discard
 pile had been altered, which should not be possible.  The estate card, specifically, was not found in 
 the hand, despite not being played, and was found in the discard pile, again despite not being played. 
 I had a difficult determining if this was my code and my previously introduced error or if this was 
 truely a bug.  All other bugs have been previously documented in bugs1.c

 
 Village:
 
 For testing adventurer, I initialized the game in a similar way to Adventurer (above) and made randomly
 assigned random decks.  The Village card allowed a player to draw one card and increase the number
 of actions by 2.  I did this by randomly assigning how many actions were to begin with and running 
 the village card effect, which adds 2 to the number of actions.  No matter how many actions there 
 were to start with, 2 were always added.  One card was also always drawn, no matter how large the 
 deck nor not depending on what was already in the deck.  
 
 No new bugs were found in Village.  
 
 I achieved 100% coverage for both Adventurer and Village, for both branch and line coverage.  
 GCOV showed that I hadn't missed any lines of code and my tests performed as expected, even
 if they didn't always pass.

*********************/
