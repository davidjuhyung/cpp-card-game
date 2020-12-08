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
  	void damage(int a);
  	int getAttack();
  	int getDefence();
  	void setAction();
  	virtual void useAbility(int activeplayer) = 0;
  	virtual void useTriggered(int activeplayer) = 0;
};

#endif
