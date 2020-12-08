#ifndef ABILITY_H
#define ABILITY_H

#include "enchantment.h"

class Ability public : Enchantment {
	bool Triggered;
  public:
  	Ability(std::string name, Board* board, std::shared_ptr<AbstractMinion> minion);
  	void useAbility(int activeplayer) override;
  	void useTriggered(int activeplayer) override;
};

#endif
