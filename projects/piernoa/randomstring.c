  The random tester prints the error message by randomly finding a string combination that
results in the s variable ( string ) being "reset\0". This satisfies one part of the
requirement to print the error message. The random string generator only has five characters
to choose from. I chose to make a character array called options and set it equal to "reset"
so that the random input string can only choose from those 5 letters ( well 4 actually because
e is repeated twice ); The last byte of 'strings' in c must be null terminated so we statically
assign a null value to the end of the string. This is not done randomly although if it were done
randomly, the random tester would still print the error message successfully, it may just take
a few more iterations.

  The inputChar function makes use of another options array, only this time it is set to "[({ ax})]"
which are the only options the testme function checks. It uses the same method as the random string
generator, that being it takes a random integer between 0 and 8 and chooses that character to return.

  Overall, after having run about 20 iterations of this test. It typically prints out the error message
in under 1000 loops, which was very surprising to me and really drove home how powerful a tool random
testing can be.
