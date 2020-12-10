#ifndef ABSTRACT_MINION_H
#define ABSTRACT_MINION_H

#include "card.h"

class AbstractMinion : public Card
{
	protected:
		int attack;
		int defence;
		int actions;
		bool gainAction = true;
		int activationCost = 0;

  public:
  	AbstractMinion(std::string name, Board* board);
  	void attackPlayer(int player);
  	void attackMinion(int player, int minion);
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
  	void setAction();
  	virtual void play(int owner, int targetPlayer, int minion = -1, bool actOnRitual = false);
  	// remember, active player as param. Use minions activated ability
    virtual void useAbility(int activeplayer, int target = -1) = 0;
    // activate trigger
  	virtual void useTriggered(int owner, int playedminion, bool isOwnerActive, When when) = 0;
    virtual std::shared_ptr<AbstractMinion> getMinion() const = 0;
};

#endif
