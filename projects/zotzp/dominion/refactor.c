/*
Cards refactored:

smithy - smithyCard()
    bugs:
        line 1261: starting value of i should be zero; village won't draw enough cards.
adventurer - adventurerCard()
    bugs:
        line 1278: changed < to <=; will draw treasure one more time than needed
village - villageCard()
    bugs:
        line 1307: line changed to only increment number of actions by 1
great hall - greatHallCard()
    bugs:
        line 1320: line to increment number of actions commented out; great hall won't increment as intended.
mine - mineCard()
    bugs:
        none
*/
