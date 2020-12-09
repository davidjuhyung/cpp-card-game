#ifndef ENCHANTMENT_H
#define ENCHANTMENT_H

#include "card.h"
#include "player.h"
#include "abstractMinion.h"
#include "minion.h"

class Enchantment : public AbstractMinion
{
	std::string enchantmentName;
	std::shared_ptr<AbstractMinion> minion = nullptr;

  public:
  	
  	Enchantment(std::string name, Board* board) : AbstractMinion{name,board} {}
  	
  	std::shared_ptr<AbstractMinion> getMinion() const override { return minion; };
};

#endif
