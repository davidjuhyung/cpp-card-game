#ifndef DELAY_H
#define DELAY_H

#include "player.h"
#include "abstractMinion.h"
#include "enchantment.h"

class Delay : public Enchantment
{
  
  public:
  
  	Delay(std::string name = "Delay", Board* board);

  	void play(int owner, int targetPlayer, int minion = 0, bool actOnRitual = false) override;

  	void useAbility(int targetplayer, int target = 0) override;

  	void useTriggered(int owner, int playedminion, bool isOwnerActive, When when) override;
};

#endif
