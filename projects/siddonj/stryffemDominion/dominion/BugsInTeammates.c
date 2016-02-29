Justin Siddon
To run my tests on Justin's code required minor adjustment of my function calls to match his. 
Three bugs were found in total. One bug was found in two separate tests independently. There seem to be bugs in the scoreFor, village, and smithy functions.

Unit Tests
Unit Test 1 - updateCoins - Pass
Unit Test 2 - ScoreFor - Fail - Misses victory cards in the deck.
Unit Test 3 - isGameOver - Pass
Unit Test 4 - gainCard - Pass

Card Tests
Card Test 1 - Smithy - Fail - Draws one too many cards. Too few cards in deck, too many in hand.
Card Test 2 - Adventurer - Pass
Card Test 3 - Village - Fail - Gives three too many actions.
Card Test 4 - Steward - Pass

Random Tests
Random Village Test - Fail - Gives three too many actions.
Random Adventurer Test - Pass




Onur Ozay
Running my tests on Onur's code required no adjustment due to the similarities in which we implemented our card functions.
Two bugs were found. One affecting the scoreFor function and another affecting the Adventurer function.

Unit Tests
Unit Test 1 - updateCoins - Pass
Unit Test 2 - ScoreFor - Fail - Misses victory cards in the deck.
Unit Test 3 - isGameOver - Pass
Unit Test 4 - gainCard - Pass

Card Tests
Card Test 1 - Smithy - Pass
Card Test 2 - Adventurer - Pass
Card Test 3 - Village - Pass
Card Test 4 - Steward - Pass

Random Tests
Random Village Test - Pass
Random Adventurer Test - Fail - Affects other players' hands and states, instead of the current player's. 
Symptoms: Wrong cards in player's hand (added cards should be treasures only), other players' hand count and deck count changed by adventurer cardEffect.




Andrew Pierno
Running my tests on Andrew's code required no adjustment due to the similarities in which we implemented our card functions.
Two bugs were found. One occurs in the scoreFor function and another in the adventurer function.

Unit Tests
Unit Test 1 - updateCoins - Pass
Unit Test 2 - ScoreFor - Fail - Misses victory cards in the deck.
Unit Test 3 - isGameOver - Pass
Unit Test 4 - gainCard - Pass

Card Tests
Card Test 1 - Smithy - Pass
Card Test 2 - Adventurer - Adventurer hangs indefinitely. I suspect that the number of treasures drawn may not be getting counted correctly, resulting in an infinite loop.
Card Test 3 - Village - Pass
Card Test 4 - Steward - Pass

Random Tests
Random Village Test - Pass
Random Adventurer Test - Adventurer hangs indefinitely. I suspect that the number of treasures drawn may not be getting counted correctly, resulting in an infinite loop.
