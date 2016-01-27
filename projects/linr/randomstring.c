Random Testing Quiz 2

This random tester should print the error message and exit out of the while loop once the s string variable equals "reset\0" and
the state equals 9. At first I tried implementing pure random testing using rand() by generating random characters and
string characters, but this resulted in an infinite loop and the error message never being printed. I then narrowed the
range for rand() to be from characters 'e-t', as "reset" only uses letters within this range. I also manually set the last 
character of the string equal to the null terminator. However this still resulted in an infinite loop with the error message 
never being displayed. Finally, I created a character array called choices, which contained the 4 letters 'r, e, t, s'.
The rand() function could only choose from these 4 letters. This resulted in the error message being printed after about
750-1000 iterations.
