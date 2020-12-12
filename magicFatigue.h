#ifndef MAGIC_FATIGUE_H
#define MAGIC_FATIGUE_H

#include "enchantment.h"

class MagicFatigue : public Enchantment 
{
  public:
		MagicFatigue(std::string name, Board* board);
		void play(int owner, int targetPlayer, int minion = -1, bool actOnRitual = false, bool testing = false) override;
		void useAbility(int activePlayer, int targetPlayer, int minion = -1, bool testing = false) override;	
		void useTriggered(int owner, int playedMinion, bool isOwnerActive, When when) override;
		std::shared_ptr<AbstractMinion> getMinion(bool forDisplay = false) override;
};

#endif
