/*
Code Coverage:

dominion.c:
	Lines executed: 33.16% of 573
	Branches executed: 30.24% of 410
	Taken at least once: 26.83 of 410
	Calls executed: 18.75% of 96

unitTest1:
	Function:	updateCoins()
	Lines executed:100.00% of 33
	Branches executed:100.00% of 8
	Taken at least once:100.00% of 8
	Calls executed:100.00% of 12

	Implications:
		Coverage is very good for the updateCoins() function.  All branches and 
		statements are being covered.

unitTest2:
	Function:	isGameOver()
	Lines executed:100.00% of 23
	Branches executed:100.00% of 12
	Taken at least once:100.00% of 12
	Calls executed:100.00% of 7

	Implications:
		Coverage is very good for the isGameOver() function.  All branches and 
		statements are being covered.


unitTest3:
	Function:	getCost()
	Lines executed:84.21% of 19
	Branches executed:100.00% of 8
	Taken at least once:62.50% of 8
	Calls executed:80.00% of 10

	Implications:
		The getCost() function uses a switch statment to determine which card has been 
		chosen.  In the inherent design of a switch statement, not all values will be
		chosen.  

unitTest4:
	Function:	gainCard()
	Lines executed:88.37% of 43
	Branches executed:100.00% of 10
	Taken at least once:50.00% of 10
	Calls executed:76.19% of 21

	Implications:
		The gainCard() function tests the toFlag variable to determine where to add the 
		given card.  This leads in a reduced coverage of lines and calls.  Those taken at
		least once is because the supplyCount was enver less than 1.


cardTest1:
	Function:	playSmithy()
	Lines executed:87.18% of 39
	Branches executed:100.00% of 16
	Taken at least once:50.00% of 16
	Calls executed:64.29% of 14

	Implications:
		100% branch coverage.
		All other coverage's are not 100% as I beleive this is a product of the discardCard
		function not dsicarding cards properly, as discuessed in bug1.c.


cardTest2:
	Function:	playAdventurer()
	Lines executed:88.89% of 27
	Branches executed:100.00% of 6
	Taken at least once:50.00% of 6
	Calls executed:70.00% of 10

	Implications:
		100% branch coverage.
		I did not test the playAdventurer function using an empty deck, which lead to less
		coverage than desireable.  In future tests, I will need to add these tests.

cardTest3:
	Function:	playVillage()
	Lines executed:88.89% of 27
	Branches executed:100.00% of 6
	Taken at least once:50.00% of 6
	Calls executed:70.00% of 10

	Implications:
		100% branch coverage.
		All other coverage's are not 100% as I beleive this is a product of the discardCard
		function not dsicarding cards properly, as discuessed in bug1.c.

cardTest4:
	Function:	playGreatHall()
	Lines executed:88.89% of 27
	Branches executed:100.00% of 6
	Taken at least once:50.00% of 6
	Calls executed:70.00% of 10

	Implications:
		100% branch coverage.
		All other coverage's are not 100% as I beleive this is a product of the discardCard
		function not dsicarding cards properly, as discuessed in bug1.c.







*/