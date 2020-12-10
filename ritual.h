#ifndef RITUAL_H
#define RITUAL_H

#include "player.h"
#include "card.h"
#include "abstractMinion.h"

class Ritual : public Card {
	std::string description;
	int activationCost;
	int charges;
  public:
  	Ritual(std::string name, Board* board);

  	void play(int owner, int targetPlayer, int minion = -1, bool actOnRitual = false) override;
  	// if isOwnerActive is false, then the playedminion is owned by the enemy
	void useAbility(int owner, int playedminion, bool isOwnerActive, When when);

	int getCharges() const;

	void recharge();
};

#endif
