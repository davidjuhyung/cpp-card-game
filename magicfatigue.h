#ifndef MAGICFATIGUE_H
#define MAGICFATIGUE_H

#include "player.h"
#include "abstractMinion.h"
#include "enchantment.h"

#include 
class MagicFatigue : public Enchantment {
  public:
	MagicFatigue(std::string name = "Magic Fatigue", Board* board);
	void play(int player, int minion) override;
  	void useAbility(int activeplayer, int target) override;
  	void useTriggered(int activeplayer, int target) override;
};

#endif
