#ifndef GIANT_H
#define GIANT_H

#include "enchantment.h"

class GiantStrength public : Enchantment {
  public:
  	GiantStrength(std::string name = "Giant Strength", Board* board, Minion* minion = nullptr);
  	void useAbility(int activeplayer) override;
  	void useTriggered(int activeplayer) override;
};

#endif
