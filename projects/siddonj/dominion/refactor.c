Changes to Code

smithy
  Created 'playSmithy()' method.
  Changed for loop from '<' to '<='.
  User will draw one extra card.


adventurer
  Created 'playAdventurer()' method.
  Changed the conditional statement checking the card type drawn from 'cardDrawn == copper'
  to 'cardDrawn != copper'.
  Will allow user to reveal copper cards and not count towards revealed treasure total.

remodel
  Created 'playRemodel()' method.
  Changed the discard statement immediately following call to gaincard()
  so the 'trash' flag is set. Will trash the card instead of discarding it.

village
  Created 'playVillage()' method.
  Changed the add action statement to add 4 actions instead of 2.
