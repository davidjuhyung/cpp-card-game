#ifndef ABSTRACTMINION_H
#define ABSTRACTMINION_H

#include "card.h"

class AbstractMinion : public Card
{
	int attack;
	int defence;
	int actions;
	bool gainAction = true;
	int activationCost = 0;

  public:

  	AbstractMinion(std::string name, Board* board);

  	// pass target playernum as param
  	void attack(int player);

  	// pass target playernum as param
  	void attack(int player, int minion);

  	void damage(int d);

  	int getDefence() const;

  	int getAttack() const;

  	int getAction() const;

  	bool gaining() const;

  	int getActivationCost() const;

    void incrementAttack();

  	void setAction();

  	virtual void play(int player, int minion = 0, bool actOnRitual = false);

  	// remember, active player as param
  	virtual void useAbility(int activeplayer, int target = 0) = 0;
  	
  	// remember, active player as param. Also, turn = false represents start of the turn, and turn = true
    // represents end of the turn
  	virtual void useTriggered(int activeplayer, int target = 0, bool turn) = 0;
};

#endif
