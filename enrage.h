#ifndef ENRAGE_H
#define ENRAGE_H

#include "enchantment.h"

class Enrage : public Enchantment
{
  
  public:
  
  	Enrage(std::string name = "Enrage", Board* board);

  	void play(int player, int minion = 0, bool actOnRitual = false) override;

  	void useAbility(int targetplayer, int target) override;

  	void useTriggered(int targetplayer, int target) override;
};

#endif
