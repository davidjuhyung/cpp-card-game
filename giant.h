#ifndef GIANT_H
#define GIANT_H

#include "player.h"
#include "abstractMinion.h"
#include "enchantment.h"

class GiantStrength : public Enchantment
{
  
  public:

  	GiantStrength(std::string name = "Giant Strength", Board* board);

  	void play(int player, int minion = 0, bool actOnRitual = false) override;

  	void useAbility(int activeplayer, int target, bool turn) override;

  	void useTriggered(int owner, int playedminion, bool isOwnerActive, When when) override;
};

#endif
