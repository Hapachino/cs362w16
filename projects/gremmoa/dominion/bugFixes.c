/*
 * I received the following bug reports from Spencer Winlaw:
 * Too many cards received when Smithy Card is played
 * To fix this, I removed the inclusive iteration in the for loop in playSmithy
 * and made it exclusive so it only draws 3 cards instead of 4.
 *
 * Silver and Gold Cards not received when Adventurer Card is played
 * To fix this, I fixed playAdventurer to increase drawnTreasure to increase
 * when a copper or a silver or a gold is found instead of when a copper or a
 * silver AND gold is found (which is not possible)
 *
