Philip Jones
CS362 - Winter 2016

/*********************************

The tests I built for buyCard(), isGameOver(), 
shuffle(), and discardCard() didn't find any 
errors. That doesn't mean that there weren't any,
of course-- my tests could have glaring 
deficiencies that I didn't see, and it's possible
that something slipped past the radar. But in
general, 100% pass means that those specific
functions are probably working OK.

The card tests, however, were another story.
I had modified three of the ones I ran tests
for already when we introduce bugs earlier this
term-- I changed the Adventurer, Smithy, and
Village card functions, so I knew off the bat that
they would be buggy.

Village:
- the played village card was never discarded (I introduced)

Adventurer: 
- draws one less treasure than supposed to (I introduced) 

Smithy:
- four cards are drawn instead of 3 (I introduced)

Great_Hall:
- the number of actions didn't go up by 1


*********************************/