#ifndef MAGICFATIGUE_H
#define MAGICFATIGUE_H

#include "player.h"
#include "abstractMinion.h"
#include "enchantment.h"

#include 
class MagicFatigue : public Enchantment {
  public:
	MagicFatigue(std::string name = "Magic Fatigue", Board* board);
	void play(int owner, int targetPlayer, int minion = -1, bool actOnRitual = false) override;
  	void useAbility(int activeplayer, int target = -1) override;
  	void useTriggered(int owner, int playedminion, bool isOwnerActive, When when) override;
};

#endif
