#ifndef ABILITY_H
#define ABILITY_H

#include "enchantment.h"

class Ability : public Enchantment
{
	bool Triggered;
	int activationCost;

  public:

  	Ability(std::string name, Board* board, std::shared_ptr<AbstractMinion> minion);
  	
  	void play(int player, int minion = 0, bool actOnRitual = false) override;
  	
  	void useAbility(int targetplayer, int target) override;
  	
  	void useTriggered(int targetplayer, int target) override;
};

#endif
