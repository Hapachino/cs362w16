Introduced Bugs

playCouncilRoom: i is used in two loops but is not set to 0 before using
in second loop

playSmithy: For loop is inclusive of 3 rather than exclusive (iterates 4 times
total)

playAdventurer:  cardDrawn comparison checks that it is copper OR silver AND
gold, so only copper cards will ever increment drawnTreasure.

playRemodel:  Pass in j variable into discardCard as trashFlag.  Whenever the
player chooses a card that is not the first card in their hand, this will result
in the discarded card being trashed.