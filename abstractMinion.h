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

    // decrease defence by d
  	void damage(int d);

  	int getDefence() const;

  	int getAttack() const;

    void setDefence(int d);

    void setAttack(int a);

  	int getAction() const;

    // return true if the minion will gain actions at the start of the turn
  	bool gaining() const;

  	int getActivationCost() const;

    // increase attack by 1
    void incrementAttack();

  	void setAction();

  	virtual void play(int player, int minion = 0, bool actOnRitual = false);

  	// remember, active player as param. Use minions activated ability
  	virtual void useAbility(int activeplayer, int target = 0) = 0;
  	
    // activate trigger
  	virtual void useTriggered(int owner, int playedminion, bool isOwnerActive, When when) = 0;

    virtual std::shared_ptr<AbstractMinion> getMinion() const = 0;
};

#endif
