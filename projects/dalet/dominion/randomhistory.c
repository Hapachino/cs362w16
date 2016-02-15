/*

Using the new random tests vs my older card unit tests coverage increased inside dominion.c Before I wasn't checking things such as when it shuffled, or if there werent enough 
cards to draw, or treasure for the adventurer card.  By creating everything randomly and running the tests hundreds of time i was able to get coverage into those random brances inside
dominion.c.  However when everything was completely random, and I didn't know exactly what was being tested i had to rely on putting more printf statements so that I could track what 
was making the errors.  While this took longer to prep the test than the other unit tests, it was easier to just sit back and run the test many many times and look for errors. 

One thing I noticed was tracking certain bugs seemed harder when it was random if there were more than 1 bug present.  When running smithy test because it draws one extra card it will also
then put one extra card it there is a problem with hand count, and deck count.  This seems like it could be two bugs but it was just the one because it took the extra from the deck and put 
it in the hand. A much less obvious bug to track with the random testing was the bug inside adventurer where silver doesnt count towards the coin count.  The way I have the random cards being
put in the deck and discard pile I didn't know what coins were acctually present.  I tracked that there were at least 2 coins (any coin) so i knew it shoudl work but then it didnt.  This can
be attributed to it not counting a certain kind of coin, or possibly just from the deck, or not from the discard.  While it makes it so I know there is something going wrong, it wasnt as obvious
as when i just filled a deck with silver and found silver wasnt being counted.  

However I think even though its harder to maybe figure out exactly what the bug is, by doing the random testing you can find bugs that you dont think about to check.  If you are hard coding
every single test, and you just dont happen to think about something, it will never be found.  I think this is why random testing can be so powerful, and while looking at coverage, and its 
increase in coverage is a meaningful thing.



*/