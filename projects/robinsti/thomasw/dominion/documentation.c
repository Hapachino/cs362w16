/*
Name: Will Thomas
Class: CS 362
Homework 2
1/17/2016

Smithy Card: 
The Smithy card uses a for loop to call the drawCard() function 3 times, placing 
3 cards into the player's hand. Once complete the discardCard function is called. 
I will explain discarding below.

Adventurer Card:
The Adventurer Card is meant to draw cards until the player draws 3 treasure cards.
All non treasure cards are then moved to the discard pile. The function creates a temp
array that stores the newly drawn cards. It also tracks card drawn and counts treasure
drawn. 

The function uses a while loop to check the drawn treasure conditional, and then
loops through a card draw. If the card is treasure it keeps it, otherwise it decrements
which effectively drops the last drawn card.

discardCard():
This function accepts the player info and gameState struct, and handPos. 
It removes the card at handPos from the player's hand and moves it to the played or trashed pile, 
depending on whether or not the trashFlag is set. If moved to the trashed pile it is 
removed from the game. If it is played, the played card count also goes up.

Hand position is decremented, hand count is decremented. If the player has more
cards in hand, discarded card is replaced with the last card in hand. All of this utilizes
various settings in the gameState struct.

Params: hand position int, player id, player gamestate struct, trashflag int
returns: 0;

updateCoints():
This function uses a for loop to iterate through the players hand. It uses conditional
statements to find copper, silver and gold cards. When it does it converts them into 
an appropriate number of coins for the player. Copper = 1, Silver = 2, Gold = 3. It also
adds any bonus.

Params: player number, player gamestate, bonus value
returns: 0

