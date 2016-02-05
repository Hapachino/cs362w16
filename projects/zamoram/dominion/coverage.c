gcov outputs the following:
Lines executed:28.27% of 566
Branches executed:22.06% of 417
Taken at least once:20.62% of 417
Calls executed:21.00% of 100

	My unit and card tests were excellent in terms of statement and branch coverge. Almost all covered
100% of the code
-function shuffle called 552 returned 100% blocks executed 100%
-function buyCard called 202 returned 100% blocks executed 100%
-function isGameOver called 5 returned 100% blocks executed 100%
-function discardCard called 6490 returned 100% blocks executed 89%
-function playSmithy called 500 returned 100% blocks executed 100%
-function playAdventurer called 500 returned 100% blocks executed 100%
-function playVillage called 500 returned 100% blocks executed 100%
-function playCouncil_Room called 5400 returned 100% blocks executed 100%

	Discard card function is the only one that misses a branch during testing. It seems no test covered the possibility
of only having one card in the player's hand when discarding a card.
	While looking through the gcov output, I noticed there were other function that I wasn't setting out to test that also
came back with 100% branch coverage, e.g. the drawCard function.
	I believe that my takes might have been lacking a little in boundary testing and in the future, I'll need to take a closer
look into testing these boundaries. A few of my unit tests do not test for each possible number of players. Some 
loop through a few test case while others are hard coded to just two players. I did this because I felt that when testing 
something like buying a card, the function isn't affected by how many players there are or which player is buying. This is a
bit of an assumption, I admit, which is why a thorough test suite should include it anyway. A final example where I did 
not properly test boundaries was with drawing cards into a hand. In card test 4 for the council room card, if I tested for cases
up to the max hand count allowed, the test would report sometimes that a player was not dealt a card. What is strange is that
the hand counts were not even close; sometimes they were off by 300, other times the call to playCouncil_Room would put the
player's hand count at -1. I believe the issue must be for cases where the hand, deck, and discard count were close to 500 for each
or for at least two. When a shuffle occurs, it might push one of the counts over the max, causing a loss of cards or some other overflow.