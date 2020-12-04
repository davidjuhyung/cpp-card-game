#ifndef ENCHANTMENT_H
#define ENCHANTMENT_H

#include "minion.h"

class Enchantment public : AbstractMinion {
	Minion* minion;
  public:
  	Enchantment(std::string name, Board* board, Minion* minion = nullptr);
    void play(int player, int minion) override;
};

#endif
