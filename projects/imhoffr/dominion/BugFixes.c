/*********************
Regina Imhoff
imhoffr@oregonstate.edu
CS 362 Winter 2016
Assignment 5

 
 playAdventurer:
    changed the line:
        while(z-1>0
    to 
        while(z-1>=0)
    This fixes the off by one error that stops the final card in temp hand from
    being copied to the played cards.
 
    In addition, I added a statement of z <= MAX_HAND since the z number would occasionally 
    be in the thousands.  The corrected line is now:
    
 while(z-1>=0 && z <= MAX_HAND){
    state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
    z=z-1;
 }
 
 playSmithy:
    changed the line
        for(i=1; i <=3; i++)
    to 
        for(i = 0; i < 3; i++)
 
    Fixing the issue where there were only 2 cards being drawn instead of the
    required 3.  This fixes the bug I introduced **for(i=1; i <=3; i++)** and
    fixes a proble with the i <= 3, so now it will draw exactly 3 cards.
 
 playCouncilRoom:
    fixed the line
        state->numBuys+=2;
    to
        state->numBuys++;
 
    Fixing the error where the number of buys is increased by 2 instead of
    being increased by 1.
 
 playSeaHag
    fixed the line
        if (i = currentPlayer){
    to 
        if (i != currentPlayer){
 
    This fixes the problem Lynn had with the curse being assigned
    to the wrong person.
 
 
 *********************/
