
randomtestcard - smithy development
I started development of my new random tests by reviewing the lecture material
and following the instructor's directions. During the example, he asks about
how many of the inputs we can generate randomly. So the very first thing I did
was find the inputs that my smithy function used which are the hand position
and game state. I just used random() to find a number between 1-5 to generate
a relatively sane hand position. For the game state, I created random inputs
for seed and hand position and initialized a new game. After the game was
initialized I changed some of the inputs randomly: hand, deck, discard counts.
I stacked the hand and deck with random cards. Once I had my inputs generated
randomly I checked the handcount, playedcount, deckcount, discardcount,
victory and kingdom card counts pre and post function call. It was able to
pick up the same bugs my card test did which was the one I implemented.

  Coverage
  File 'dominion.c'
  Lines executed:18.59% of 581
  Branches executed:17.49% of 423
  Taken at least once:13.95% of 423

  The play smithy function had 100% coverage which was good. But, because of
  all of my conditional statements for errors not all of my testing function
  was executed so the coverage isn't entirely representative.

  File 'randomtestcard.c'
  Lines executed:64.63% of 147
  Branches executed:90.91% of 44
  Taken at least once:54.55% of 44
  Calls executed:47.37% of 57


randomtestadventurer - adventurer development
I began my development for this random test the same way I approached my
smithy function by looking at what the inputs were and generating them
randomly. I just used random() to find a number between 1-5 to generate
a relatively sane hand position. For the game state, I created random inputs
for seed and hand position and initialized a new game. After the game was
initialized I changed some of the inputs randomly: hand, deck, discard counts.
I stacked the hand and deck with random cards. Once I had my inputs generated
randomly I checked the handcount, playedcount, deckcount, discardcount,
victory and kingdom card counts pre and post function call. It was able to
pick up the same bugs my card test did which was the one I implemented ( acts
as if a treasure card is drawn on each conditional statement).

  Coverage
  File 'dominion.c'
  Lines executed:24.44% of 581
  Branches executed:21.28% of 423
  Taken at least once:17.97% of 423
  Calls executed:13.08% of 107

  Like the play smithy function, the play adventurer function had 100% coverage
  even with my bug. However, like my random test for play smithy I did not recieve
  100% coverage on my test.

  Lines executed:54.59% of 207
  Branches executed:60.61% of 66
  Taken at least once:37.88% of 66
  Calls executed:47.13% of 87
