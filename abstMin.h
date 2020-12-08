#ifndef ABSTMIN_H
#define ABSTMIN_H

#include "card.h"

class AbstractMinion public : Card {
	int attack;
	int defence;
	int actions;
	bool gainAction = true;
  public:
  	AbstractMinion(std::string name, Board* board);
  	void attack(int player);
  	void attack(int player, int minion);
  	int getDefence();
  	void setAction();
  	virtual void play(int player, int minion);
  	virtual void useAbility(int activeplayer) = 0;
  	virtual void useTriggered(int activeplayer) = 0;
};

#endif
