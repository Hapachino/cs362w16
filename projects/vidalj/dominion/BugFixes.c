/*

==Fixing Bugs Found By Team==

Per a bug reported by a teammember, it was discovered that  under certain circumstances  Smithy could draw
the wrong number of cards.  The report stated that this was dependant upon the posiiton of the Smithy card
in the players hand.  I removed that depenancy in the function and made Smithy draw the same amount of 
cards(3) without regard to it's position.

There was another bug report from another teammember for village missing a card once it was finished but I
was able to trace the test case back to not accounting for the card being held in playedCardCount waiting
to be discarded.


==Fixing Bugs Placed in Program By Me==

smithyEffect(): This bug was discovered by one of my teammembers and I have fixed it as part of that part
of the assignment.

adventurerEffect(): The bug introduced here was that adventurer would only search for copper and silver, so
I added back the ability to also search for gold.

villageEffect(): The bug introduced to villageEffect was that  the number of actions would increase by 2
multiplied by the number of cards in the players hand. This was fixed by having actions increase by exactly
2.

councilRoomEffect(): The bug here was that an extra card was drawn to a total of 5.  I reduced that back to
4.

*/