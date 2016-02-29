Bug fix #1: Smithy discards wrong card. This bug was fixed by removing the " + 1" from  'handpos + 1' in the call to the discard function. 
The discard function must be called on the handpos variable in order to discard the smithy.

Bug fix #2: Not enough cards discarded  for adventurer: the index z is used to keep track of how many cards are to be discarded. These are the
non-treasure cards as found while searching for 2 treasure cards. The while loop that discards these cards counts down to z >= 0. However,
the bug in this code was that the loop only counted down to z > 0, which fails to discard the 0th indexed card. The loop was set correctly.

Bug fix #3: Adventurer card itself does not get discarded: this is self explanatory, there is no call to the discard function in order to discard
the Adventurer card itself. A discard call was added.   
