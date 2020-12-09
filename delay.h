#ifndef DELAY_H
#define DELAY_H

#include "enchantment.h"

class Delay : public Enchantment
{
  
  public:
  
  	Delay(std::string name = "Delay", Board* board);

  	void play(int player, int minion = 0, bool actOnRitual = false) override;

  	void useAbility(int targetplayer, int target) override;

  	void useTriggered(int targetplayer, int target) override;
};

#endif