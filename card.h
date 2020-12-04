#ifndef CARD_H
#define CARD_H

#include "board.h"

class Card {
	std::string name;
	Board* board;
  public:
  	Card(std::string name, Board* board) : name{name}, board{board} {}
  	virtual play(int player, int minion) = 0;
};

#endif
