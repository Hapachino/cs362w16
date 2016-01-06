Jana Gallina
CS362 Fall 2015
Assignment 2
October 11, 2015

Documentation should contain your understanding of smithy and adventurer cards (code). It should also contain 
documentation of your understanding of discardCard() and updateCoins() method.  Keep your documentation short, 
though there is no upper limit. Documentation.txt file should contain at least 100 words.  


Smithy: The smithy uses the drawCard function to draw 3 cards, and then calls the discardCard function to end 
the turn.

Adventurer: While the drawntreasure count is less than 2, drawCard is called to draw a card and cardDrawn 
identifies the card. If the card is a treasure, drawntreasure is incremented. If the card is not a treasure,
the card is added to the temphand which is discarded at the end of the turn along with the regular hand.

discardCard(): If the trashFlag is set to less than 1 (meaning the card is played rather than trashed), 
the card is discarded to the played pile. Then if the last card was played or there is only one card in hand, 
the handCount is decremented and then turn is over. Otherwise the card in hand will replace the discarded 
card on top of the pile and the handCount is decremented.

updateCoins(): The updateCoins function tallies the number of coins available to spend if a bonus is applied 
from the played card. It grants one coin for each copper, two for each silver, and three for each gold.
