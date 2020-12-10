#ifndef GIANT_STRENGTH_H
#define GIANT_STRENGTH_H

#include "enchantment.h"

class GiantStrength : public Enchantment
{
  public:
    GiantStrength(std::string name, Board* board);
  	void play(int owner, int targetPlayer, int minion = -1, bool actOnRitual = false) override;
  	void useAbility(int activePlayer, int target = -1) override;
  	void useTriggered(int owner, int playedMinion, bool isOwnerActive, When when) override;
};

#endif
