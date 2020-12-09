#ifndef ABSTRACTMINION_H
#define ABSTRACTMINION_H

#include "card.h"

class AbstractMinion : public Card
{
	int attack;
	int defence;
	int actions;
	bool gainAction = true;

  public:

  	AbstractMinion(std::string name, Board* board);

  	// pass target playernum as param
  	void attack(int player);

  	// pass target playernum as param
  	void attack(int player, int minion);

  	int getDefence() const;

  	int getAttack() const;

  	int getAction() const;

  	bool gaining() const;

  	void setAction();

  	virtual void play(int player, int minion = 0, bool actOnRitual = false);

  	// remember, target player as param
  	virtual void useAbility(int targetplayer, int target = 0) = 0;
  	
  	// remember, active player as param
  	virtual void useTriggered(int targetplayer, int target = 0) = 0;
};

#endif
