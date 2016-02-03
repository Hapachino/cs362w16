The unit tests I decided to do were getCost(), updateCoins(), scoreFor(), and isGameOver.
When I ran my unit tests I did not find any bugs in getCost and updateCoins. 

For scoreFor, the unit test said that the discard score was not accurate. When I went 
back and looked at the function, I believe this is becuase the deck was adding a score 
to it. Even thought the test had set deckCount to 0, scoreFor was not using deckCount 
for counting the deck's score but instead using the discardCount. So the deck score 
portion of the code was grabbing data it should not have been accessing and adding it 
to the score.

For isGameOver, the unit test said that when the function got to card 25, sea had, the
function did not register that the pile was empty. So when it and two others were empty
the game did not say it was over. Going back to look at the function, I saw that the
for loop checking all the cards to see if their pile is 0 only goes to card 24 instead
of card 26.

The card tests I decided to do were smithy, adventurer, gardens, and sea hag. When I 
ran my card tests the only card that passed was the gardens card.

For the smithy card, the card test says that smithy did not discard the smithy card.
When you go look at the implemenation of the card it does call discardCard. The problem
was that discardCard does not move the card to the discard pile but instead to a 
playCards array and count, which is not used in the implemenation of the game. This
results in the card being essentially being trashed.

For both the adventurer card and sea hag card, the card tests also said that the 
discard pile didn't have enough cards. When I went back and looked at that adventurer 
function, while the drawn cards that were not treasure cards were discarded, the 
adventurer card never gets discarded, resulting in the discard pile lacking 1 card.
The same thing happened with the sea hag card, as the top card from the decks of other
players were discarded but the sea hag card from the hand of the current player was
never discarded.