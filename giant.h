#ifndef GIANT_H
#define GIANT_H

#include "enchantment.h"

class GiantStrength : public Enchantment {
  public:
  	GiantStrength(std::string name = "Giant Strength", Board* board);
  	void play(int player, int minion) override;
  	void useAbility(int activeplayer, int target) override;
  	void useTriggered(int activeplayer, int target) override;
};

#endif
