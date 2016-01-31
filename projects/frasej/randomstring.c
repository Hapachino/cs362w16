Jennifer Frase
random test quiz 2

Development:
	I wasn't sure what kind of implementation testme() had so I was not sure
	to what degree of randomness the inputChar and inputString functions needed to
	have. So I came up with the long (but reasonable) version and the very short,
	you already know what characters are being looked for, version. The first was
	for if a person is asked to input any reasonable character . So this
	test is simulating actual people without much guidelines on what they can input
	(only that the string has to be 5 characters long and be lowercase letters). 
	However, I know from pure probability that the likelyhood of getting the error 
	message was exceedingly small. Just inputString alone would have about a 1 in 
	12 million chance but then there is the inputChar on top of that.
	
	So I also decided to implement a tester where the user is given the possible
	characters to advance the state (just not the ordering) for the random character
	and where the user can only use letters from the word reset. I tried out the
	various combinations to compare the iteration times (not including using both
	long versions at the same time). The inputChar long and inputString short took
	anywhere from 600 to 5 thousand iterations, the short inputChar and long 
	inputString took about 15 million iteration, and the short inputChar and short 
	inputString took anywhere from about 300 to 2000 iterations.
	
	From this I determined that since there wasn't really much difference between
	inputChar's long and short functions that I would leave the long version active.
	However, as I suspected inputString's long version really does take a long time,
	so I didn't want to use it. I though about possibly making a tester that used more
	than the letters 'r','e','s', and 't', but I couldn't figure out a scenario where
	a user would use more than that but not the whole alphabet (lowercase only). 
	In addtion I thought maybe the user doesn't know that the string has to be 5 letters,
	but then I would have to decided what was the normal lengths that people would
	input because otherwise I would have to include exceedingly long strings. Since
	I didn't know how to scale the size of the string down to reasonable lengths, I 
	decided to stick with the short version I had.
	
Finding the error message:
	The long versions of inputChar simply returns the random ascii value of a
	character that a user might use on the keyboard. The short version for inputString
	takes the characters in rest and randomly picks an index, saving the letter in
	rest at that index into a different 5 letter string. It will do this once for each
	index in the 5 letter string, generating a random 5 letter string using only r,e,s,t.
	Once inputChar generates the 9 characters in the right order (not squentially), then
	inputString has to result in the word reset before the error message will be found.
	
