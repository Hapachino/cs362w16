This assignment was much more difficult than I had originally thought
it was going to be. 

My original design of the random tester was to initialize a game with
a different seed about 100000 times and this would give me different
combinations of a shuffled deck. This also would give me at least 
most of the cases of the tests. I quickly realized that I had an issue
with being able to know ahead of time what cards were going to be where,
which is something that I relied on in my tests for assignment 3 because
I manually placed each card in the deck or in the hand. I realized
that I could not account for the reshuffle since I did not know the
order of the cards after the reshuffle. This causes my random tests
to not be as thorough of tests as assignment 3, but I still found
basic issues.

My tests catch a bug in every iteration of the game because it tests
the basic functionality of the cards. The bugs that I introduced in
adventurer make it so that the handcount does not decrease. I was 
surprised to see that this was not an infinite loop since it was 
previously, but it still caught that something was not working.

The bug in the smithy card was easy to catch, since it did not draw
3 cards when there were 3 cards available. I threw in extra tests, which
would probably almost never be executed, but still possible. I checked
for if there are only 2 or 1 or 0 drawable cards (which means either
all the cards are trashed or in the hand) and then correctly accounts 
for it. 

My coverage for dominion.c was about 30%, which is about what I exepected
since my assignment 3 coverage was below that, but I did not utilize a
full game. In assignment 4, I just played lots of random games and 
made sure to play and test the card in each game. This would cause 
my coverage to go up, but since I am still not using most of the 
functions in dominion.c, it is what I would expect. 

I have found there to be a bug that I am specifically NOT checking for,
but I wonder if I should be. When a card is played, it does not end up
in the discard pile during end turn. I did not test for this because
that is a feature of endTurn, not playing either of the cards. It does
however affect my tests since it plays through a game and loses cards
along the way. 

I did have a lot of issues when I switched to the OSU servers. For 
some reason, the OSU servers do not like my countTreasures function. 
I did not have enough time to debug this, but I think it has to do with
how it is accessing each card for handCard. 

Overall, the random tester for these cards I believe are not up to par. 
Another design I could have chosen is to randomly populate the deck and
discard pile with cards as if the game was mid progress, but I think it 
would still end up with the same result. If I were to improve this 
test further, I would create a separate function that mimics the 
play_adventurer function and then check each individual step within it. 
This is more of a black box tester.