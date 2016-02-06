The random string generator simply takes all valid ASCII values as the character argument. 
In this way, we can relatively quickly get all of the conditionals to be executed, getting to 
case 9 quickly. The method I first tried was to then implement a completely random character
generator in order to try and achieve the string "reset". However, this method takes very long.
Instead, I created a switch statement that gives only the characters 'r', 'e', 's', and 't' in order
to arrive at the desired outcome sooner. With the first method, the program ran several million
iterations for several minutes and never reaching the goal. With the switch statement method, I was
consistently able to complete the program with the desired error message in less than a second.
