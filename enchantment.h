#ifndef ENCHANTMENT_H
#define ENCHANTMENT_H

#include "abstractMinion.h"

class Enchantment : public AbstractMinion
{
  protected:
	std::string enchantmentName;
	std::string enchantmentDescription;
	std::shared_ptr<AbstractMinion> minion = nullptr;
  public:
  	Enchantment(std::string name, Board* board);
  	card_template_t displayCard() override;
  	std::vector<card_template_t> inspectMinion() override;
};

#endif
