Philip: 
Adventurer

What I had to change: in order to fix my code, all I had to do was use his dominion.h and .c files, and then update my name to his, which was playAdventureuer, instead of mine, which was myAdvnetureer. The change was minimal. 

For his code, I wish I would have told it to only print if it was, because I caught an error every run (100,000 times) of them. 

Error - drawn treasure was set to 1 instead of 0. I noticed this because I was expecting 2+ cards to be drawn, however only 1 was, making the numbers always at least one off. 

Smithy

Just like with adventurer, I had to change the name to playSmithy instead in order to run the code. That was the only change I had to make. I did fix my output, because through copy and pasting, I didn’t update the names of my hand output to hand.

Bug - Draws 4 cards instead of 3. 
Description: Deck was one less, hand was on more, and the smithy wasn’t properly discarded. 


Richard:

Richard's code had a few more quirks. He had a playSmithy and playAdventuerer in his header file, but cardRefractoredSmithy and adventurer in his main file. 

Adventurer:
bug - Discards one or more less card than supposed to. 
description - Discard was one or more off each time. The difference was between expected and actual. Happened for most cards. 
How to reproduce-  Run make test1

Smithy - 
Bug example - 
Hand: expected 3, actual 2
Deck: expected 16, actual 17
Smithy not on top of deck. 
Description - Hand has one too many, deck has one to few, smithy isn’t at top of discard.  This happened for every card, not just one. 
How to reproduce: run make test 2 