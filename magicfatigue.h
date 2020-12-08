#ifndef _MAGICFATIGUE_H_
#define _MAGICFATIGUE_H_
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
