#ifndef DELAY_H
#define DELAY_H

#include "enchantment.h"

class Delay : public Enchantment
{
  public:
  	Delay(std::string name, Board* board);
  	void play(int owner, int targetPlayer, int minion = -1, bool actOnRitual = false) override;
  	void useAbility(int activePlayer, int targetPlayer, int minion = -1) override;
  	void useTriggered(int owner, int playedMinion, bool isOwnerActive, When when) override;
  	std::shared_ptr<AbstractMinion> getMinion(bool forDisplay = false) override;
};

#endif
