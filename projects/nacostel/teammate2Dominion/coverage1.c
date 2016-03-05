// gcov outpout

File 'dominion.c'
Lines executed:17.13% of 578
Branches executed:15.83% of 417
Taken at least once:14.15% of 417
Calls executed:7.37% of 95

// isGameOver()
function isGameOver called 5 returned 100% blocks executed 100%

// discardCard()
function discardCard called 90 returned 100% blocks executed 88%

// shuffle()
function shuffle called 414 returned 100% blocks executed 93%

// buyCard()
function buyCard called 202 returned 100% blocks executed 100%

- Blocks executed is on the high side for all 4 unit tests, but 
  both shuffle and discardCard tests could be improved. For the
  discardCard function the scenario where the player has only one
  card in hand is not tested. For shuffle the scenario where the
  player's deckCount is less than 1 is not tested.

- isGameOver could probably use additional tests since 5 is a small
  sample size. Some branches were only tested 1 time - hardly
  all encompassing.

- For the future, increasing the sample size may be beneficial. 
  The lectures spoke of waiting significant periods of time for tests
  to run to be sure they are thorough. Mine executed after a short 
  couple second delay. This is probably indicative of a lack of a 
  sample size as well as not testing the boundaries. 
