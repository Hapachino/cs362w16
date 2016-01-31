/*
Matt Walz
Random Testing Quiz 2

To get the testme() function to generate the error message, it is necessary for the 'state' variable to equal 9 and the c-string 's' to equal "reset" with a trailing '\0' character. The 'state' variable is initialized as zero and it increments only when the 'c' variable is equal to a particular ASCII printable character (a different character for each increment. e.g. '[' from 0 to 1 and 'a' from 4 to 5).

So, in order to randomly generate the required ASCII characters to increment 'state', the inputChar() function uses a random number generator to generate a number within the range of 32 to 127 inclusive (this range of numbers represents the decimal codes for the ASCII printable characters). This entire range was included even though there are only 9 unique characters which increment the 'state' variable as a way to test the function behavior over the entire range of printable characters. In four runs of the code the 'state' variable reached a value of 9 after 957 iterations, 474 iterations, 719 iterations, and 812 iterations.

To be able to randomly generate the required c-string as well as test the system capability on a variety of inputs, the inputString() function randomly generates c-strings of length 1, 6, 11, 16, or 21 characters. The last character in all the strings is the '\0' character while the rest of the characters are randomly selected from the set of (a, e, r, s, t, Z, !). These parameters were chosen in order to test the system on a variety of string lengths (1 to 21) and character values (a, Z, and ! as boundary cases for lowercase, uppercase, and punctuation) while still providing a high enough probability of generating the required 'reset\0' string to generate the error condition in no more than a few hundred thousand iterations. As you can see from my run results below, the code was indeed successful at accomplishing this goal. In fact, on the very first run we got extremely lucky and generated the correct string after only 2038 iterations (accomplished on iteration 2995, but it took the first 957 iterations to get 'state' equal to 9). The average number of iterations required to generate the error c-string in the four runs (calculated as the total iterations minus the number of iterations required to set the 'state' variable equal to 9) was 107835 iterations.


Run 1:
Iteration 2990: c = \, s = !etrZ, state = 9
Iteration 2991: c = @, s = Zasst!Zt!sZseZeserrr, state = 9
Iteration 2992: c = U, s = r!rsetr!!Z, state = 9
Iteration 2993: c = M, s = rrrZa!esae!etes!etrs, state = 9
Iteration 2994: c = f, s = ZstZssseZs, state = 9
Iteration 2995: c = z, s = reset, state = 9


Run 2:
Iteration 196272: c = b, s = aZZtseZtstaeeZt, state = 9
Iteration 196273: c = 3, s = , state = 9
Iteration 196274: c = t, s = Z!rrZtrZrsr!sZt, state = 9
Iteration 196275: c = >, s = !tZae, state = 9
Iteration 196276: c = 5, s = reset, state = 9


Run 3:
Iteration 89831: c = `, s = r!retrtats, state = 9
Iteration 89832: c = r, s = , state = 9
Iteration 89833: c = >, s = r!srr, state = 9
Iteration 89834: c = k, s = s!es!te!rrerra!sZZae, state = 9
Iteration 89835: c = \, s = reset, state = 9


Run 4:
Iteration 145192: c = E, s = rttZsZsatr, state = 9
Iteration 145193: c = T, s = rZrterrsZatZt!strert, state = 9
Iteration 145194: c = i, s = a!st!a!r!!, state = 9
Iteration 145195: c = ^, s = e!eea, state = 9
Iteration 145196: c = r, s = reset, state = 9
*/
