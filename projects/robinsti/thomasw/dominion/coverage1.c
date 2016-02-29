/*
Coverage Report:
For dominion.c as a whole:

I had 29.74% coverage 
I had 34.77% branch execution
Calls executed: 20.00%

For the cards and functions I specifically tested I had excellent, near 100% coverage and block execution. 
It seems like most of the branches I miss in the functions and cards I test are fall through cases. I think
I need to be more aware of capturing every use case, as I find myself trying to test for the specific return value.

I think the overall code coverage is low because I tested cards with fewer lines of code. Some of them are quite large and have a huge number of branches.

I also think this is dependent on what functions you test and what functions they call. Many of the functions call a series of others to check game state and the like.
I also tested for card effects specifically rather than entire end to end processes. I think the number implies that I'd want to do the latter for more complete coverage.