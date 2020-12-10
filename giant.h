#ifndef GIANT_H
#define GIANT_H

#include "player.h"
#include "abstractMinion.h"
#include "enchantment.h"

class GiantStrength : public Enchantment
{
  
  public:

  	GiantStrength(std::string name = "Giant Strength", Board* board);

  	void play(int owner, int targetPlayer, int minion = -1, bool actOnRitual = false) override;

  	void useAbility(int activeplayer, int target = -1) override;

  	void useTriggered(int owner, int playedminion, bool isOwnerActive, When when) override;
};

#endif
