These tests are intended to cover the following units within dominion.c:
- int _adventurer()
- int _smithy()
- int _village()
- council_room case of cardEffect()
- int buyCard()
- int discardCard()
- int isGameOver()
- int scoreFor()

Going into greater detail about coverage within each of these:

### _adventurer() ###
    Complete coverage. Every line of code in this function was called at least once; the branch that was called least was the "empty-deck" branch, calling shuffle() before drawing cards if the deck was empty. The function was only tested once in this condition.
    A boundary case that was not tested is the case that this card is used when less than two treasure cards exist in the deck; while extremely unlikely in actual gameplay, this case is theoretically possible and would cause an infinite loop if not checked for.
    
### _smithy() ###
    Complete coverage. Each statement in this function was called at least once. The only two cases that were tested on this function were essentially "deck >= three cards" or "deck < three cards". This was sufficient for full statement and branch coverage.
    
### _village() ###
    Complete coverage. Every statement in the function was called at least once. There is no branching in this function, so the test cases related more to the proper drawing and discarding of cards.
    
### council_room - cardEffect() ###
    Every statement in the council_room case was called at least once. This function was tested with a random number of other players and in the cases of "deck less than four cards" and "deck greater than or equal to four cards".

### buyCard() ###
    Coverage for this function was nearly complete; the only branch that was not called was a "coins < cost" condition. Because this branch was supposed to be tested, this shows a deficiency in the test code. However, all tests in this function passed, so this is the only way we can see that that test passed for an unintended reason. (The supply was not reset from the previous test, so instead, the "supply < 1" branch was called twice.)
    
### discardCard() ###
    The only statement not called from this function was for a "hand count = 1" condition. So, while the tests called discardCard() with the target card in various positions, as well as from an empty hand, this was a boundary case that was not tested. All other statements and branches were called at least once.
    
### isGameOver() ###
    Complete coverage. Every statement was called at least once. Both branches were tested, as well as cases that should have caused the function to fail, such as less than three piles empty (that did not include the province pile).
    
### scoreFor() ###
    Complete coverage. Every statement was called; there was no branching in this function. This has some interesting implications considering that every single test failed, but the exact error wasn't isolated by the tests alone. Boundary coverage, therefore, was not very high. The error is in the implementation of the calculation for "gardens," which has a variable point value - rather than counting the entire deck, the function is counting only curse cards, thanks to a misuse of fullDeckCount().
    Without knowing this, it would be very difficult to isolate the error - there are six cards that affect point values and there are many, many permutations possible to test. However, gardens might have been a good boundary case to test upon further reflection, because of its variable value and additional calculation involved, which gives it another potential point of failure.