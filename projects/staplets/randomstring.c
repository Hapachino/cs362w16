Shaun Stapleton
CS 362
Quiz 2

 Write up the development of your random tester and how it finds the error message as randomstring.c

When Implementing the random test for testme.c I initially began by going off of the ascii table and finding the
values that would match the required specifications. One early error I made out of the gates was forgetting to
add the end of line character to my string and it was in the code. That was a details error. 

After cleaning that up I was finding segmentation faults in my code, which I came to find was due to me trying
to first off assign a number to my char array and then I figured out that I needed to hone in a little further
with what I wanted. So I created an array of the word reset to eliminate other characters. Unfortunately this
set of letters ran for what I'm assuming to be a long time because I canceled after a couple tens of thousand
iterations. From there I took out the duplicate 'e' in reset and tried once more and it completed in around 
2700 iterations, which was what I was hoping for.

I then decided to really try to refine things and placed a while loop around each random call. This will isolate
the checks to each individual letter in the string. With this I will catch the word reset each time and then
it comes down to the state to get up to 9. At this point in time, the iteration total runs from 400 to about 800.