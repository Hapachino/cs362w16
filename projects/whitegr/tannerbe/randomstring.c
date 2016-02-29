I first implemented a random char function that picks a random number that represents the valid ascii numbers for characters (32 through 126). 
Then I made the random string function by simply building a string out of 5 random characters from the random char function.
After running it, it very quickly found all the required individual characters, but got stuck trying to get the right combination of random chars to make "reset".
It came as no surprise, since there is a 1 in 96^5 chance of getting it right. This meant the program would have to iterate, in theory, around 95^5 times.
I then refactored the program with a flag to limit the random chars to those between e and t (ascii 101 through 116) once it was at state 9.
This made the chance 1 in 16^5, or just over a million possibilities. Any modern computer can run through that in the amount of time it takes to make coffee.
Flip was unlucky and took 1.4 million iterations to get it right, but it still took less than a minute.