#ifndef ABILITY_H
#define ABILITY_H

#include "player.h"
#include "abstractMinion.h"
#include "enchantment.h"

class Ability : public Enchantment
{
  public:

  	Ability(std::string name, Board* board, std::shared_ptr<AbstractMinion> minion);
  	
  	void play(int player, int minion = 0, bool actOnRitual = false) override;
  	
  	void useAbility(int activeplayer, int target, bool turn) override;
  	
  	void useTriggered(int owner, int playedminion, bool isOwnerActive, When when) override;
};

#endif
