#ifndef CARD_H
#define CARD_H

#include "board.h"

class Card {
	std::string name;
	Board* board;
	int cost;
  public:
  	Card(std::string name, Board* board) : name{name}, board{board} {}
  	std::string getName() { return name; }
  	int getCost() const { return cost; }
  	virtual void play(int player, int minion) = 0; // always pass in active player as argument in play
};

#endif
