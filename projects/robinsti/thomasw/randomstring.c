Will Thomas
CS 362
Quiz 2

For the random values we are trying to find a series of random individual ascii characters, starting with parantheses through the rest of the ascii table. For the random values I just created a random generator that looks for ascii characters in that range and returns one for every iteration.

For the random string it was a similar process but we only needed lower case ascii letters. So in this instance I randomly generated 5 character arrays that each contained a random lower case ascii letter. The testme function is generating both a character and a string every iteration so you have to just generate random values for everything each time.

Since state both has to equal 9 and the string has to spell the word reset it can take many iterations. From the tests I ran you will likely hit state 9 before you generate the specific word 'reset'. It took anywhere from 500k to 9 million iterations to generate the error message.
