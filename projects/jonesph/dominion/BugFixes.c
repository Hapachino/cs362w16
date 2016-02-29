/****************
Philip Jones
CS362 - Winter 2016

Bugs found by teammates:

Bug 1.)		Smithy card
The smithy card draws too many cards in its current state, as the for loop counting the number of times a card is drawn includes a 
standard <= symbol instead of a <. To fix this bug (which I originally introduced), I merely remove the '=' from the for loop.

Bug 2.)		Adventurer card
The adventurer card draws one fewer treasures than it is supposed to. This is because value that tracks the total number of drawn
treasures, smartly named drawnTreasure, is initialized to 1 instead of 0. I introduced this bug as well. It is easily fixed by changing
the starting value back to 0.


Bugs not found by teammates:

Bug 3.)		Feast card
The feast card was giving the player 10 coins instead of the 5 as required. A simple number change was all that was needed to fix this bug
that I originally introduced.

Bug 4.)		Adventurer card
The adventurer card wasn't getting properly discarded. I had to rework the parameters (to include a hand position), then add in a discardCard()
function near the bottom of the Adventurer card functionality. 

Bug 5.)		Village card
The village card wasn't discarding itself after use, due to a bug I had previously introduced. To fix this, I merely added back in the line
and used the discardCard function to fix it.