#ifndef ENCHANTMENT_H
#define ENCHANTMENT_H

#include "minion.h"

class Enchantment public : AbstractMinion {
	std::shared_ptr<AbstractMinion> minion;
  public:
  	Enchantment(std::string name, Board* board, std::shared_ptr<AbstractMinion> minion = nullptr);
  	std::shared_ptr<AbstractMinion> getMinion();
    void play(int player, int minion) override;
};

#endif
