/*




BUG 1- discovered by unittest4.c
Found 1 bug in isGameOver:  If one of the empty piles is sea_hag or 
treasure_map, and there are 2 other empty piles elsewhere in the supply, 
this doesn't generate a 'Game Over'.  Problem is in the following (LINE 403): 

  for (i = 0; i < 25; i++)
        should be
  for (i = 0; i < 27 ; i++)



