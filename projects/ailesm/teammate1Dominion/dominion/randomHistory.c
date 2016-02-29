//Michael Byrne
//byrnemi@onid
//Assignment 4
//CS 362
//2-13-2016

/* --------------------------- assignment 4 random test analysis ---------------------- */

/*
**Test Card: Embargo**

I chose to test the embargo card because I hadn't seen it in gameplay and its primary mechanic
seems to be a bit esoteric within Dominion, making it a good target for bugs. It's a simple card
but one whose effects need to be tested further along in gameplay. That is, unlike, say, a 
Smithy card, the embargo card has a lingering effect. Only a few cards have this property. 

My initial difficulty in testing the embargo card came with its coin bonus. Coin bonuses are 
difficult to test in this Dominion implementation because they don't change the game state
player by player. That is, while it's often possible to test before and after effects in calling
the playCard function, to test coins, we need to be looking at cardEffect instead.

This was implemented as a final step after I had finalized and tested an oracle for evaluating
the supply pile effects of the embargo. This oracle works in two parts. The first is to 
determine whether an embargo does actually exist following the card being played with a random
choice of supply pile to embargo at the correct index in the embargo tokens array.

This mechanic was found to be bug-free, however, when I attempted to use the gainCard
function with the embargoed supply pile, it did not always return -1. If the embargoed
pile was (illegally) not in play, it returned -1 correctly, but failed to return -1
on an embargoed pile that was legally in the game. The function was allowed to gain a card
from the embargoed pile. I believe that this is a bug in the gainCard function. 

**Test Card: Adventurer**

Because I did my initial round of Dominion testing in Assignment 3 with random testing, this test 
is a revision of that original tester. 

I thought that my range of 50 cards in 50 hands seemed sufficient, as did my oracle, which 
operates by checking to see that the expected number of cards had been flipped, based on the
predetermined location of two treasure cards. This is a solid check.

What I noticed, however, is that I did not test cases where the player deck did not have a 
treasure at all or had only one treasure. I implemented both of these cases by removing 
either all of the treasure cards from the deck or removing all but one. I reset the 
deckCount, but did not see a reason to completely remake another random deck. Instead I 
simply reused the deck I had prepared for the general two treasure case. 

The placement of the single treasure card was chosen randomly, though this likely adds
little to the test.

No new bugs were detected, but the previously detected, intentional bug remains in place:
The card mechanics do not detect the case where the player deck is empty and needs to be
reshuffled. That is, the program fails silently in that case. 

**Coverage**

File 'dominion.c'
Lines executed:40.55% of 577
Branches executed:42.45% of 417
Taken at least once:33.81% of 417
Calls executed:26.60% of 94

In assignment 3, I achieved roughly 47 percent line coverage for all eight tests. Here, with
only two tests, I achieved 40 percent. This indicates a combination of things. One, 
assignment 4 coverage is pretty good, which is supported by a line by line examination 
the gcov output. If functions were touched at all by the testers, they were tested 100 
percent in terms of block coverage, for the most part.

It seems very likely that there is a near complete overlap between the two card functions tested
randomly here and the four single-functions tested in the first part of assignment 3, which 
will partially account for the coverage similarity between the two assignments. The fact that 
the adventure card is tested in both assignments should account for the remainder. 