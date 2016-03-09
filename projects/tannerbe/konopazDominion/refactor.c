adventurerEffect - bug introduced where if the current player's deck needs to
be reshuffled the next player's deck is reshuffled instead. ~ln 12 of function.

smithyEffect - on the for loops i increment I change from postfix to prefix
increment operator which should mean that the smithEffect will only draw 2
cards instead of 3

councilRoomEffect - the numbuys increment has a typo in it so there is no
compiler error but the number of buys is never actually updated.

mineEffect -  no intentional bugs ;)

villageEffect - "accidentally" commented out the discard call so the village
card can be played infitely
