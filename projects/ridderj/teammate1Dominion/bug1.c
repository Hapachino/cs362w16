	While testing function unit tests, I didn't discover any bugs in all but one so I'll describe some issue I encountered instead. For unittest1, I realized that I was testing with impossible
game settings such as 0 or 1 players. However, the function did not fail because of this. This shouldn't matter because I was testing the function, not the game. For unit
test 2, I was testing the shuffle() function. I tested to make sure the pre-shuffled deck did not match the post-shuffle deck but occassionally, it did. This was not a bug though,
because the smaller the deck, the more likely a shuffle would create the identical deck. A deck size of 1 or 2 is the most obvious example. I decided to use 4 as the lower boundary for deck size
and I'm comfortable with that because in a real game, it's unlikely that the deck will ever get that small.
	Finally, with unit test 4, I believe I discovered a bug in buyCard(). My test shows that the hand count was not matching what was expected after the function call. When I looked into the function,
I discovered that buyCard() calls gainCard(), which is supposed to put a card in the player's hand but instead a variable flag gets it put in the trash. This causes hand count to be one less than expected.
	Card test 1 was testing the refactored smithy function. When the function is called, the smithy card should be played into the card pile, increased the played card count. However, the played card count was
one less than expected. This caught the bug I introduced where I set the trash flag to 1 in the discardCard() function call.
	For card test 2, I was not sure how I would know how many cards were discarded to find 2 treasure cards. I did know that in order to find 2 treasure cards, the function would draw from the deck,
possibly shuffle the discarded cards into a new deck, and the hand count would increase by 2. The hand counts came out as expected but the pre deck count plus pre discard count was 1 greater than 
the post deck count plus discard count. This meant a card must be getting lost when the playAdventurer function is called. Indeed, the bug I introduced causes a card to get lost where the temp hand
does not discard the last card in the temp array.
	Card test 3 tested the refactored village function. I did not introduce a bug to this and neither did I find one in my testing.
	Finally card test 4 was to test the council room card. It allows the player to draw 4 cards and allows another buy. Additionally, all other players draw a card. My tests showed that the player was getting
an extra card when I compared the hand counts. This is in line with the bug I introduced in the refactored function. There was another bug, however, that I was unable to figure out where it was originating from.
The test will occassionally report that a player was not dealt a card and the hand counts would be off by hunderds and sometimes negative. The problem seemed to arise when that players hand, deck, and discard
counts were close to the maximum. Combining them during shuffle causedsome sort of error like an overflow. Using a test MAX_HAND/MAX_DECK solved the issue. It's a bug but one that should not exist in a sane
game: the hand cards come from the deck and the discard cards come from the hand; in the tests, they were randomly generated.