coverage.c
My test suite covered 43.15% of the lines in dominion.c.
My test suite covered 42.45% of the branches in dominion.c
My test suite covered executed 38.95% of the calls in dominion.c 

function coverage: 
initializeGame() - 83% of blocks
shuffle - 93% of blocks
playCard - 50% of blocks
buyCard - 76% of 
numHandCards - 0% of blocks
handCard - 100% of blocks
supplyCount - 100% of blocks
fullDeckCount - 0% of blocks
whoseTurn - 0% of blocks executed
endTurn - 100% of blocks
isGameOver - 0% of blocks
scoreFor - 0% of blocks
getWinners - 0% of blocks
drawCard - 36% of blocks
getCost - 93% of blocks
cardeffect - 14%
discard - 75% of blocks
gainCar - 70% of blocks
updateCoins - 80% of blocks
playAdventurer - 64% of blocks
playSmithy - 100% of blocks
playCouncil - 100% of blocks
playRemodel - 0% of blocks
playVillage - 100% of blocks

The coverage of dominion.c shows some clear areas where coverage could 
and should be improved. Most concerning are the functions that have low
coverage that I explicitly tested, such as playCard and buyCard, as well
as playAdventurer. There are also a number of functions that are not 
covered because they were not in the scope of what my testing covered,
such as isGameOver, scoreFor, and getWinners. There were also a number
of the cards that I did not test, resulting in card effect having a low
coverage percent. 
