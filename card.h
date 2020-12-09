#ifndef CARD_H
#define CARD_H

#include "board.h"

class Card

{	
	std::string name;

	Board* board;

	int cost;

  public:

  	Card(std::string name, Board* board) : name{name}, board{board} {}

  	std::string getName() { return name; }
  	
  	int getCost() const { return cost; }
  	
  	// always pass in target player as argument in play. This function is the play method for the card class. It
    // effects the board in some way depending on the type and specification
  	virtual void play(int player, int minion = 0, bool actOnRitual = false) = 0;
};

#endif
