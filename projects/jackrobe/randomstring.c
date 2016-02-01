/*

 My random tester is different for the char and the input string.

 I wanted my random tester to exercise the full set of values that elevate the state, but only elevate to state 9 on a
 rare occasion. This allowed me to get more mileage from the second random tester that is tasked with generating the
 string "reset", to trigger the error. At first it was more likely that it would get to state 9 before it generated the
 "reset" string. Because teh state is elevated as soon as one of the characters is encountered. i.e. it was no dependent
 on the combination being correct, I allow this to get to state 8, by randomly selecting from the set of possible values
 But only give the character for state 9 elevation with the odds ~1 in 50k.

 I, somewhat unnecessarily, set the function inputString() to exercise the full breadth of the
 ascii keyboard values (for fun), but generate an r, e, s, or t combination with a somewhat higher probability, namely
 50% of the time.

 In addition the function needed to put something from that data set at various positions in the string, so I made
 it make strings of random length between 0 and 10. This was done in order to exercise each "and" statement.

 I set a second integer to be a random value between  0 and 2, that it generates for example a combination of the
 aforementioned values more often than a random ascii value combination. The likelihood is then higher for it to
 generate "reset" , but less likely that this  will also occur at state 9, and trigger the error.

 */