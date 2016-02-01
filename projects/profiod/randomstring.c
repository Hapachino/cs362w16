David Profio

For the development of my random tester I was first planning on using completely random ASCII values. I then realized that since we are printing these letters that put a restriction on the domain of possible values. My next step was to decide how I wanted to limit the input. 

For the string I decided to only allow the four characters present in the final check for reset (r, s, e ,t). I chose this as it limited the domain enough to have the test run in a reasonable amount of iterations. In order to make it random I use a for loop of 5, and call rand within that for loop. I then have a switch statement after the assignment of the random number. Since there are four values there are four checks. 

For the char I decided to allow any character from a-z. I then wired it up with a switch statement and the rand function as above. After that I chose to just up the range returned by my rand function to allow for non a-z characters. Since I have a case statement I am guaranteeing that I will hit each of the characters required by the state checks. This combined with my random string generator above guarantees hitting the error while containing pseudo randomness. 