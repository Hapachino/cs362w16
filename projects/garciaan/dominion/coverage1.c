File 'dominion.c'
Lines executed:25.90% of 583
Branches executed:23.02% of 417
Taken at least once:15.83% of 417
Calls executed:18.09% of 94


I was surprised to see that there was so little code coverage, but as I 
dug through what was actually being executed, I realized that it makes sense.
I only call a few functions to for the test suite, so I can see why the
dominion code only has a little bit of it that is run. It seems to be around 
20-25% for both lines and branches. After looking at which branches were taken,
I believe that I have hit most of the if statements in those functions to
either create an error or take the unbeaten path. This percentage of code
coverage overall implies that this does not fully test dominion.c. However,
looking at the code coverage of the functions that I did test shows that these
functions were very well tested. 

One of the things that confused me the most was when I saw how many times the
drawCard function was executed. I am not sure why this number is in the
millions. I have looked through my code and there is no reason it should be
called that many times. 

One of my card tests (adventurer) did not have very good code coverage due to
the bug that was introduced. It also did not finish completing its tests. This
is because the function gets stuck in an infinite loop and the timeout
activates. I don't think there is another way to break out of that inifinite loop from the outside of the funtion unless I called a jump to the next instruction set, which I was not interested in doing for this test suite. I 
did not think it was necessary since a timeout is a good enough sign that 
something is broken and is high priority.
