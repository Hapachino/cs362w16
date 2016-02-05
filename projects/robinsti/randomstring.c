/******************************************************************************
 ** Author: Tim Robinson
 ** Date: January 31, 2016
 ** Testme Quiz
 ****

	I assumed that it was appropriate to choose reasonable constraints for the
	randomly produced values for both the inputChar() function and the 
	inputString() function.

	For the inputChar() function, I produced a range of values that includes
	the possible values to change the state variable. I made the range 4 
	ASCII characters longer than necessary, the overflow for which I convert to
	characters outside of the necessary contiguous range (this includes the 
	parens, a space, and a null character).

	For the inputString() function, I assumed much tighter constraints due to the
	possible combinations of characters. Each character is randomly selected from
	a character array containing the characters 'r', 'e', 's', 't', and a null
	character. At first, I tried to implement the inputString() function using
	the inputChar() function for each char in the random string. I quickly 
	realized that 6 continuous characters with 39 possibilities (6^39) is much
	too large of a space for the computer to create the error message.

	The constraints ended up being very important in producing the error
	message.

	Number of Iterations for 10 Cases
	---------------------------------
	5903
	17655
	8215
	7480
	2023
	9484
	1628
	21915
	208
	4534


 *****************************************************************************/
