#ifndef ENRAGE_H
#define ENRAGE_H

#include "player.h"
#include "enchantment.h"

class Enrage : public Enchantment
{
  
  public:
  
  	Enrage(std::string name = "Enrage", Board* board);

  	void play(int owner, int targetPlayer, int minion = 0, bool actOnRitual = false) override;

  	void useAbility(int targetplayer, int target = 0) override;

  	void useTriggered(int owner, int playedminion, bool isOwnerActive, When when) override;
};

#endif
