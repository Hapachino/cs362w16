/*
 Robert Jackson
 Coverage1 report
 2/2/2016
 cs 362

/*

CARDTEST1
        Function 'smithyCard'
Lines executed:100.00% of 6
Branches executed:100.00% of 2
Taken at least once:100.00% of 2
Calls executed:100.00% of 3
Same here. The only branches are the for loop and this is impossible not to hit

 CARDTEST2
        Function 'adventurerCard'
Lines executed:100.00% of 18
Branches executed:100.00% of 12
Taken at least once:83.33% of 12
Calls executed:100.00% of 3
The trick here was to set up the deck so that the deck count was 0. Also, it needed to have sets of each copper, silver and gold.

CARDTEST3
        Function 'great_hallCard'
Lines executed:100.00% of 5
No branches
Calls executed:100.00% of 2
Not much to discuss here it’s all covered.

CARDTEST4
        Function 'councilRoomCard'
Lines executed:77.78% of 9
Branches executed:66.67% of 6
Taken at least once:50.00% of 6
Calls executed:66.67% of 3
There is a piece of the council room card function that didn’t need to be executed, in order to test the card. i.e. there is a statement in there that we don’t want to have used because it’s skipping over the action. Indeed it’s not being use inferred that we don’t accidentally give the current player a card.

 UNITTEST1
        Function 'drawCard'
Lines executed:100.00% of 22
Branches executed:100.00% of 6
Taken at least once:100.00% of 6
Calls executed:100.00% of 1
This required one to run the test without cards in the deck, but with cards in the discard so with that set it then
runs though all branches.


UNITTEST2
Function 'scoreFor'
Lines executed:100.00% of 24
Branches executed:100.00% of 42
Taken at least once:100.00% of 42
Calls executed:100.00% of 3

 In order to make this one work, I had to set it up so that it ran though all the potential scoring cards, and then
 used a few combinations  of those in different places, the deck the hand and the discard. It quickly found the
 bug in the calculation. Though, it was easier to see it upon code review!

UNIT TEST 3
Function 'gainCard'
Lines executed:100.00% of 13
Branches executed:100.00% of 6
Taken at least once:100.00% of 6
Calls executed:100.00% of 1
The gain Card Test, managed to execute 100% of the branches. Those Firstly it needed to try an use a supply that was
exhausted, This  I achieved by trying to put one of each type of card into the players Hand. Then, each of those cards
are used in one of the three flags that are set, which covers the other branches.

UNIT TEST4
Function 'discardCard'
Lines executed:100.00% of 13
Branches executed:100.00% of 6
Taken at least once:100.00% of 6
No calls
I might not understand what ”no calls” means then because it is explicitly called more than once in the function,
Obviously it achieves good coverage. The trick to that was that there is a trash flag. I called the function once with
the trash flag on and once with it off to cover this branch.


* */