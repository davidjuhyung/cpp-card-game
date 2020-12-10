#ifndef DELAY_H
#define DELAY_H

#include "enchantment.h"

class Delay : public Enchantment
{
  public:
  	Delay(std::string name, Board* board);
  	void play(int owner, int targetPlayer, int minion = -1, bool actOnRitual = false) override;
  	void useAbility(int activeplayer, int target = -1) override;
  	void useTriggered(int owner, int playedminion, bool isOwnerActive, When when) override;
};

#endif
