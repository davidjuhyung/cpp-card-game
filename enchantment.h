#ifndef ENCHANTMENT_H
#define ENCHANTMENT_H

#include "minion.h"

class Enchantment public : AbstractMinion {
	std::shared_ptr<AbstractMinion> minion = nullptr;
  public:
  	Enchantment(std::string name, Board* board) : AbstractMinion{name,board} {}
  	std::shared_ptr<AbstractMinion> getMinion() const { return minion; };
};

#endif
