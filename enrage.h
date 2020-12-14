#ifndef ENRAGE_H
#define ENRAGE_H

#include "enchantment.h"

class Enrage : public Enchantment
{
  public:
  	Enrage(std::string name, Board* board);
  	void play(bool testing, int owner, int targetPlayer, int minion = -1, bool actOnRitual = false) override;
  	void useAbility(int activePlayer, int targetPlayer, int minion = -1, bool testing = false) override;
  	void useTriggered(int owner, int playedMinion, bool isOwnerActive, When when) override;
  	std::shared_ptr<AbstractMinion> getMinion(bool forDisplay = false) override;
};

#endif
