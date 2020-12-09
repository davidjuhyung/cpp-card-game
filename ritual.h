#ifndef RITUAL_H
#define RITUAL_H

#include "card.h"

class Ritual : public Card {
	std::string description;
	int activationCost
	int charges;
  public:
  	void play(int player, int minion = 0, bool actOnRitual = false) override;
  	// if isOwnerActive is false, then the playedminion is owned by the enemy
	void useAbility(int owner, int playedminion, bool isOwnerActive, When when);
};

#endif
