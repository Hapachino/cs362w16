Refactored the following functions from the switch statement into their own functions:
playSmithy(), playAdventurer(), playFeast(), playRemodel and playMine(). I also changed the headers
in the dominion.h file to match the new function headers of the functions above. There
were bugs introduced purposely as well. These bugs will not issue any compiler warnings
or errors. Feast and Mine cards now grant additional advantages while Smithy is now less
powerful and Adventurer is useless.


Bugs
playSmithy() bug
- only adds 2 cards instead of 3
- Trash flag is set to 1 so card is not discarded but trashed

playAdventurer() bug
- game thinks they gain a treasure card on each conditional statement

playFeast() bug
- allows 15 coins to buy instead of 5
- instead of setting x = 0 to end the loop it adds 0 to x creating an
  infinite loop

playMine() bug
- Instead adding a card to the player's hand it adds to the deck instead

playRemodel() bug
- Instead of discarding the card it trashes it instead

scoreFor() bug
- score not calculated correctly, might have bug in full deck count()

playVillage() bug
- not properly discarding card
