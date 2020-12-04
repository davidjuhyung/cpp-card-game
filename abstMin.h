#ifndef ABSTMIN_H
#define ABSTMIN_H

#include "card.h"

class AbstractMinion public : Card {
	int attack;
	int defence;
	int actions;
	bool gainAction = true;
  public:
  	AbstractMinion(std::string name, Board* board) : Card{name, board} {}
  	void attack(int player);
  	void attack(int player, int minion);
  	virtual useAbility(int activeplayer) = 0;
  	virtual useTriggered(int activeplayer) = 0;
};

#endif
