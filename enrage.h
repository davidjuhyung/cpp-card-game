#ifndef ENRAGE_H
#define ENRAGE_H

#include "player.h"
#include "enchantment.h"

class Enrage : public Enchantment
{
  
  public:
  
  	Enrage(std::string name, Board* board);

  	void play(int owner, int targetPlayer, int minion = -1, bool actOnRitual = false) override;

  	void useAbility(int activeplayer, int target = -1) override;

  	void useTriggered(int owner, int playedminion, bool isOwnerActive, When when) override;
};

#endif
